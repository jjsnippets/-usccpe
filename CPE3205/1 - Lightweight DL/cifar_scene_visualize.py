# CPE 3205 - EMERGING TECHNOLOGIES IN CPE
# GROUP 2   TTh 12:00NN - 1:30PM LB264TC
# Team 13: Linga, Cielo Jevana; Maravillas, Ma Jullianna; Sarcol, Joshua        BS CpE - 3    2026/03/11
# Deep Learning Exercise and Technical Report

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
import os

### 0. Error handling
# Ensure the required files exist before proceeding
model_path = 'cifar_scene_cnn.keras'
image_path = 'input.png'

if not os.path.exists(model_path):
    raise FileNotFoundError(f"Model file '{model_path}' not found.")
if not os.path.exists(image_path):
    raise FileNotFoundError(f"Input image '{image_path}' not found.")

### 1. Set-up
# Load the trained model
model = tf.keras.models.load_model(model_path)

### 2. Layer visualizations
# 2.1. layers[0]: the Conv2D layer
first_layer_output = model.layers[0].output
feature_extractor = tf.keras.Model(inputs=model.inputs, outputs=first_layer_output)

# Load and preprocess the image
img = tf.keras.preprocessing.image.load_img(image_path, target_size=(32, 32))
img_array = tf.keras.preprocessing.image.img_to_array(img)
input_batch = np.expand_dims(img_array, axis=0)

# Generate the feature maps
features = feature_extractor.predict(input_batch)
num_filters = features.shape[-1] 
#   1 image, 30x30 spatial dimensions, and 32 different filters

# Plot the 32 feature maps in a 4x8 grid
fig, axes = plt.subplots(4, 8, figsize=(16, 8))
fig.suptitle('First Layer (Conv2D) Feature Maps', fontsize=16)

for i in range(num_filters):
    row = i // 8
    col = i % 8
    ax = axes[row, col]
    
    # Extract the 2D image for the i-th filter
    feature_image = features[0, :, :, i]
    
    # Plot using the 'viridis' colormap to highlight activation intensities
    ax.imshow(feature_image, cmap='viridis')
    ax.axis('off')
    ax.set_title(f"Filter {i}", fontsize=9)

plt.tight_layout()
plt.savefig("L1_Convolutional Feature Maps.png", bbox_inches='tight')



# 2.2. layers[1]: the MaxPooling2D layer
pool_layer_output = model.layers[1].output
pool_extractor = tf.keras.Model(inputs=model.inputs, outputs=pool_layer_output)

# Generate the pooled features
pooled_features = pool_extractor.predict(input_batch)
#   The shape of pooled_features will be (1, 15, 15, 32)
#   (halved spatial dimensions from 30x30 to 15x15)

# Plot the 32 pooled feature maps in a 4x8 grid
fig2, axes2 = plt.subplots(4, 8, figsize=(16, 8))
fig2.suptitle('Second Layer (MaxPooling2D) Feature Maps', fontsize=16)

for i in range(num_filters):
    row = i // 8
    col = i % 8
    ax = axes2[row, col]
    
    # Extract the 2D image for the i-th pooled filter
    pooled_image = pooled_features[0, :, :, i]
    
    # Plot using the same colormap for consistency
    ax.imshow(pooled_image, cmap='viridis')
    ax.axis('off')
    ax.set_title(f"Pool {i}", fontsize=9)

plt.tight_layout()
plt.savefig("L2_Pooled Feature Maps.png", bbox_inches='tight')


# 2.3: Layers[3]: the Dense layer
dense_layer_output = model.layers[3].output
dense_extractor = tf.keras.Model(inputs=model.inputs, outputs=dense_layer_output)

# Generate the dense features (shape: 1, 128)
dense_activations = dense_extractor.predict(input_batch)[0]

# Normalize the activations to a [0, 1] range for coloring/sizing
max_val = np.max(dense_activations)
if max_val > 0:
    normalized_activations = dense_activations / max_val
else:
    normalized_activations = dense_activations

# Plot the cells in a 8x16 grid for display
rows, cols = 8, 16
x_coords = []
y_coords = []
colors = []
sizes = []

for i in range(128):
    row = i // cols
    col = i % cols
    
    x_coords.append(col)
    y_coords.append(rows - 1 - row) # Invert row so 0 is at the top
    
    # Darker color and larger size for higher activations
    activation_val = normalized_activations[i]
    colors.append(activation_val)
    sizes.append(50 + (activation_val * 300)) # Base size 50, scales up to 350

fig3, ax3 = plt.subplots(figsize=(12, 6))
fig3.suptitle('Fourth Layer (Dense) Activations', fontsize=16)
scatter = ax3.scatter(
    x_coords, 
    y_coords, 
    s=sizes, 
    c=colors, 
    cmap='Blues', 
    alpha=0.8, 
    edgecolors='grey', 
    linewidth=1,
    norm=mcolors.PowerNorm(gamma=0.5, vmin=0.0, vmax=1.0)
)
ax3.set_xlim(-1, cols)
ax3.set_ylim(-1, rows)
ax3.set_xticks([])
ax3.set_yticks([])
ax3.set_aspect('equal')
ax3.axis('off')
cbar = plt.colorbar(scatter, ax=ax3, fraction=0.03, pad=0.04)
cbar.set_label('Normalized Activation', rotation=270, labelpad=15)
plt.tight_layout()

plt.savefig("L4_Dense Activations Grid.png", bbox_inches='tight')


# 2.4: Layer[4]: the output Dense layer
output_layer = model.layers[4].output
output_extractor = tf.keras.Model(inputs=model.inputs, outputs=output_layer)

# Generate the final probabilities (shape: 1, 5)
final_probabilities = output_extractor.predict(input_batch)[0]

# Setup for the 5 output nodes in a single row
ClassLabels = {0: 'Cloud', 1: 'Forest', 2: 'Mountain', 3: 'Plain', 4: 'Sea'}
num_classes = len(ClassLabels)
x_coords_out = np.arange(num_classes)
y_coords_out = np.zeros(num_classes) # All on the same horizontal line

# Sizes and colors based directly based on probabilities [0.0 to 1.0]
colors_out = final_probabilities
sizes_out = 100 + (final_probabilities * 900) 

# Plot the output nodes
fig4, ax4 = plt.subplots(figsize=(10, 3))
fig4.suptitle('Final Output Layer (Softmax Probabilities)', fontsize=14)

scatter_out = ax4.scatter(
    x_coords_out, 
    y_coords_out, 
    s=sizes_out, 
    c=colors_out, 
    cmap='Reds', 
    alpha=0.8, 
    edgecolors='grey', 
    linewidth=1.5,
    vmin=0.0, 
    vmax=1.0
)

# Use the class names from ClassLabels for the text labels
labels = [ClassLabels[i] for i in range(num_classes)]
for i, class_name in enumerate(labels):
    text_str = f"{class_name}\n{final_probabilities[i]*100:.1f}%"
    ax4.text(x_coords_out[i], -0.15, text_str, ha='center', va='top', fontsize=11)

# Clean up axes
ax4.set_xlim(-0.5, num_classes - 0.5)
ax4.set_ylim(-0.5, 0.5)
ax4.axis('off')

# Add a horizontal colorbar
cbar2 = plt.colorbar(scatter_out, ax=ax4, orientation='horizontal', fraction=0.05, pad=0.2)
cbar2.set_label('Probability', labelpad=10)

plt.tight_layout()
plt.savefig("L5_Output Layer Probabilities.png", bbox_inches='tight')


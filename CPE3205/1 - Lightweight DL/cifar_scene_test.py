# CPE 3205 - EMERGING TECHNOLOGIES IN CPE
# GROUP 2   TTh 12:00NN - 1:30PM LB264TC
# Team 13: Linga, Cielo Jevana; Maravillas, Ma Jullianna; Sarcol, Joshua        BS CpE - 3    2026/03/11
# Deep Learning Exercise and Technical Report

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
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

# Class labels
ClassLabels = ['Cloud', 'Forest', 'Mountain', 'Plain', 'Sea']

# Load and preprocess the image
img = tf.keras.preprocessing.image.load_img(image_path, target_size=(32, 32))
img_array = tf.keras.preprocessing.image.img_to_array(img)
input_batch = np.expand_dims(img_array, axis=0)
#       Expand dimensions to create a batch of 1: (1, 32, 32, 3)



### 2. Class Prediction
prediction_probs = model.predict(input_batch)[0]
pred_idx = np.argmax(prediction_probs)



### 3. View results
fig = plt.figure(figsize=(12, 2.5))
gs = gridspec.GridSpec(1, 3, width_ratios=[1.2, 1.2, 1.6])
plt.subplots_adjust(wspace=0.5)

# Image portion
ax_img = fig.add_subplot(gs[0, 0])
ax_img.imshow(img)
ax_img.axis('off')

# Prediction portion
ax_pred = fig.add_subplot(gs[0, 1])
ax_pred.axis('off')

summary_text = (
    f"Image: {image_path}\n\n"
    f"Predicted class:\n  {pred_idx} — {ClassLabels[pred_idx]}\n\n"
    f"Confidence:\n  {prediction_probs[pred_idx]*100:.2f}%"
)
ax_pred.text(0.0, 0.5, summary_text, fontsize=10, va='center', ha='left')

# Probability portion
ax_prob = fig.add_subplot(gs[0, 2])
ax_prob.axis('off')

prob_lines = [f"{ClassLabels[j]}: {prediction_probs[j]*100:.2f}%" for j in range(len(ClassLabels))]
prob_text = "All Probabilities:\n" + "\n".join(prob_lines)

ax_prob.text(0.0, 0.5, prob_text, fontsize=10, va='center', ha='left')

# Bounding box
fig.canvas.draw()
b1 = ax_img.get_position()
b2 = ax_pred.get_position()
b3 = ax_prob.get_position()

left = min(b1.x0, b2.x0, b3.x0) - 0.01
right = max(b1.x1, b2.x1, b3.x1) + 0.01
bottom = min(b1.y0, b2.y0, b3.y0) - 0.03
top = max(b1.y1, b2.y1, b3.y1) + 0.03

rect = plt.Rectangle(
    (left, bottom), right - left, top - bottom,
    transform=fig.transFigure, fill=False, edgecolor='blue', linewidth=1.5
)
fig.patches.append(rect)

plt.savefig("output.png", bbox_inches='tight')

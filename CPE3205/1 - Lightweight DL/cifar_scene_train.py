# CPE 3205 - EMERGING TECHNOLOGIES IN CPE
# GROUP 2   TTh 12:00NN - 1:30PM LB264TC
# Team 13: Linga, Cielo Jevana; Maravillas, Ma Jullianna; Sarcol, Joshua        BS CpE - 3    2026/03/11
# Deep Learning Exercise and Technical Report

import tensorflow as tf
import numpy as np
# import pandas as pd
# import os
# import sys
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec


### 1. Data Preparation
# 1.1 Load the entire CIFAR-100 coarse dataset
#   First tuple (train_images, train_labels) for all 50,000 training images and their coarse labels
#   Second tuple (test_images, test_labels) for all 10,000 test images and their coarse labels
(coarse_TrainImages, coarse_TrainLabels), (coarse_TestImages, coarse_TestLabels) = tf.keras.datasets.cifar100.load_data(label_mode='coarse')

# Check if all coarse classes have been properly loaded; expected is [0 ... 19]
# print('Coarse Class: {}'.format(np.unique(coarse_TrainLabels)))

# 1.2 Load the entire CIFAR-100 fine dataset
#   First tuple (fine_TrainImages, fine_TrainLabels) with 500 training images per class
#   Second tuple (fine_TestImages, fine_TestLabels) with 100 testing images per class
(fine_TrainImages, fine_TrainLabels), (fine_TestImages, fine_TestLabels) = tf.keras.datasets.cifar100.load_data(label_mode='fine')

# Check if all fine classes have been properly loaded; expected is [0 ... 99]
# print('Fine Class for all: {}'.format(np.unique(fine_TrainLabels)))

# 1.3 Building the training subset containing the "large natural outdoor scenes" coarse class (index 10)
# 1.3.1 Collecting indexes
idx = []
for i in range(len(coarse_TrainLabels)):
  if coarse_TrainLabels[i] == 10:
    idx.append(i)

# Check if all indexes are properly collected; expected is 500 per class * 5 classs = 2,500
# print('Total images with 10 coarse label (large natural outdoor scenes) from TRAINING DATASET: {}'.format(len(idx)))
idx = np.array(idx)

# 1.3.2 Collecting images and labels
subset_TrainImages = fine_TrainImages[idx]
subset_TrainLabels = fine_TrainLabels[idx].flatten()

# Check if all training images are properly collected; expected is (2500, ...)
# print("Shape of the image training dataset:{}".format(subset_TrainImages.shape))
# print('Fine Class for the extracted training images:{}'.format(np.unique(subset_TrainLabels)))

# 1.4 Building the testing subset containing the "large natural outdoor scenes" coarse class (index 10)
# 1.4.1 Collecting indexes
idx = []
for i in range(len(coarse_TestLabels)):
 if coarse_TestLabels[i] == 10:
  idx.append(i)

# Check if all indexes are properly collected; expected is 100 per class * 5 classs = 500
# print('Total images with 10 coarse label (large natural outdoor scenes) from TESTING DATASET: {}'.format(len(idx)))
idx = np.array(idx)

# 1.4.2 Collecting images and labels
subset_TestImages = fine_TestImages[idx]
subset_TestLabels = fine_TestLabels[idx].flatten()

# Check if all testing images are properly collected; expected is (500, ...)
# print("Shape of the image testing dataset: {}".format(subset_TestImages.shape))
# print('Fine Class for the extracted testing images:{}'.format(np.unique(subset_TestLabels)))

# 1.5 Relabel classes subset to start from 0
ClassIndex = np.unique(subset_TrainLabels)

for i in range(len(ClassIndex)):
  for j in range(len(subset_TrainLabels)):
    if subset_TrainLabels[j] == ClassIndex[i]:
      subset_TrainLabels[j] = i

  for j in range(len(subset_TestLabels)):
    if subset_TestLabels[j] == ClassIndex[i]:
      subset_TestLabels[j] = i

# 1.6 Visualize some training images
ClassLabels = {0: 'Cloud', 1: 'Forest', 2: 'Mountain', 3: 'Plain', 4: 'Sea'}
plt.figure(figsize=(8,8))
plt.suptitle("Sample training images")
for i in range(25):
  plt.subplot(5,5,i+1)
  plt.xticks([])
  plt.yticks([])
  plt.grid(False)
  plt.imshow(subset_TrainImages[i])
  plt.xlabel(ClassLabels[int(subset_TrainLabels[i])])
plt.tight_layout(rect=[0, 0, 1, 0.95])

plt.savefig("Sample training images.png", bbox_inches='tight')



### 2. Building the model
# 2.1. Specifying model layers
# Sequential model: layers added one at a time
model = tf.keras.Sequential()

# Input layer: Training and testing images (input_shape argument below)
#   Layer size: 32 x 32 x 3

# Hidden layer 1: 32 convolution filters ("features" / "neurons"); each of size 3 x 3 for all color channels at once
#   Layer size: 30 x 30 x 32
#   Parameters: 3 x 3 x 3 = 27 weights for the kernel
#               1 for the bias
#               then for each of the 32 filters
#               (27 + 1) x 32 = 896
model.add(tf.keras.layers.Conv2D(32, kernel_size=(3, 3), activation='relu', input_shape=(32, 32, 3)))

# Hidden layer 2: Max pooling layer for downsampling; filter size of 2x2, stride of (2, 2)
#   Layer size: 15 x 15 x 32
model.add(tf.keras.layers.MaxPooling2D(pool_size=(2, 2)))

# Hidden layer 3: Flattening layer; reshape previous 3D layer to 1D
#   Layer size: 7200
model.add(tf.keras.layers.Flatten())

# Hidden layer 4: Fully connected layer
#   Layer size: 128
#   Parameters: 7,200 inputs x 128 outputs = 921,600 weights
#               128 biases, 1 for each output
#               921,600 + 128 = 921,728
model.add(tf.keras.layers.Dense(128, activation='relu'))

# Output layer: One for each of the possible fine class labels
#   Layer size: 5
#   Parameters: 128 inputs x 5 outputs = 640 weights
#               5 biases, 1 for each output
#               640 + 5 = 645
model.add(tf.keras.layers.Dense(len(ClassIndex), activation='softmax'))

# Print-out of model layers and parameters
model.summary()



### 3. Model training
# Specifying how the model will be trained
#   Adaptive Moment Estimation (adam) optimizer
#       Weights that consistently get large gradients are updated more cautiously, while weights with small gradients can get relatively larger updates.
#   Sparse categorical crossentropy loss function
#       For multi-class classification models where the labels are integers [0 1 ...]
#       If the model gives high probability to the correct class, the loss is small; if it gives low probability, the loss is large.
#   Sparse categorical accuracy metric
#       Compares the index of the largest predicted probability to the integer label.
#       Counts how many predictions are correct, and reports accuracy = correct / total.
model.compile(optimizer='adam', 
        loss='sparse_categorical_crossentropy',
        metrics=[tf.keras.metrics.SparseCategoricalAccuracy()])

# Training the actual model using the training subset; 10 epochs, and 10% of the training data used for validation
metricInfo = model.fit(subset_TrainImages, subset_TrainLabels, epochs=10, validation_split=0.1)



### 4. Model Evaluation
# Plotting the training and validation accuracy of the model per epoch
acc = metricInfo.history['sparse_categorical_accuracy']
val_acc = metricInfo.history['val_sparse_categorical_accuracy']
epochs = range(1, len(acc) + 1)

plt.clf()
plt.plot(epochs, acc,  marker='o', linestyle='-', color='g', label='Training accuracy')
plt.plot(epochs, val_acc, marker='o', linestyle='-', color='b', label='Validation accuracy')
plt.title('Training and Validation accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.savefig("Model accuracy.png", bbox_inches='tight')

# Check for overfitting: Plotting training loss and validation loss of the model per epoch
loss = metricInfo.history['loss']
val_loss = metricInfo.history['val_loss']
epochs = range(1, len(loss) + 1)

plt.clf()
plt.plot(epochs, loss, marker='o', linestyle='-', color='g', label="Training loss")
plt.plot(epochs, val_loss, marker='o', linestyle='-', color='b', label='Validation loss')
plt.title('Training vs Validation loss')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.savefig("Model loss.png", bbox_inches='tight')

# Zoomed in plot with y-axis limited to [0, 2.5]
plt.clf()
plt.plot(epochs, loss, marker='o', linestyle='-', color='g', label="Training loss")
plt.plot(epochs, val_loss, marker='o', linestyle='-', color='b', label='Validation loss')
plt.ylim(0, 2.5)
plt.title('Training vs Validation loss (zoomed)')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.savefig("Model loss_zoomed.png", bbox_inches='tight')

# From the generated plots comparing training and validation loss, the validation loss starts to increase at epoch 5.
# This indicates that the model trained for 10 epochs may be slightly overfit.
# Stopping at epoch 4 with validation accuracy of ~65% may be the best option.

# Save model
model.save("cifar_scene_cnn.keras")



### 5. Model Testing
# 5.1. Testing using the entire test image subset
print("\n\n\n")
print(f"Total number of test images: {len(subset_TestImages)}")

test_loss, test_acc = model.evaluate(subset_TestImages, subset_TestLabels)
print(f"Test accuracy: {test_acc:.2%}")

# 5.2. Viewing individual results
print("\n\n\n")
print("Testing on sample images...")
classification = model.predict(subset_TestImages)
num_images = 10
fig = plt.figure(figsize=(12, num_images * 2.5))

gs = gridspec.GridSpec(num_images, 3, width_ratios=[1.2, 1.2, 1.6])
plt.subplots_adjust(hspace=0.4, wspace=0.5)

for i in range(num_images):
    # Image column
    ax_img = fig.add_subplot(gs[i, 0])
    ax_img.imshow(subset_TestImages[i])
    ax_img.axis('off')

    # Prediction summary column
    ax_pred = fig.add_subplot(gs[i, 1])
    ax_pred.axis('off')

    true_idx = subset_TestLabels[i]
    pred_idx = np.argmax(classification[i])
    is_correct = (true_idx == pred_idx)
    status_text = "Correct" if is_correct else "Incorrect"
    status_color = "green" if is_correct else "red"

    summary_text = (
        f"True class:\n  {true_idx} — {ClassLabels[true_idx]}\n\n"
        f"Predicted class:\n  {pred_idx} — {ClassLabels[pred_idx]}\n\n"
        f"Status:\n  {status_text}"
    )

    ax_pred.text(0.0, 0.5, summary_text, fontsize=10, va='center', ha='left')

    # Probability column
    ax_prob = fig.add_subplot(gs[i, 2])
    ax_prob.axis('off')

    probs = classification[i]
    prob_lines = [f"{ClassLabels[j]}: {probs[j]*100:.2f}%" for j in range(len(ClassLabels))]
    prob_text = "Probabilities:\n" + "\n".join(prob_lines)

    ax_prob.text(0.0, 0.5, prob_text, fontsize=10, va='center', ha='left')

    # Bounding box
    fig.canvas.draw()
    b1 = ax_img.get_position()
    b2 = ax_pred.get_position()
    b3 = ax_prob.get_position()

    left = min(b1.x0, b2.x0, b3.x0) - 0.01
    right = max(b1.x1, b2.x1, b3.x1) + 0.01
    bottom = min(b1.y0, b2.y0, b3.y0) - 0.01
    top = max(b1.y1, b2.y1, b3.y1) + 0.01

    rect = plt.Rectangle(
        (left, bottom),
        right - left,
        top - bottom,
        transform=fig.transFigure,
        fill=False,
        edgecolor=status_color,
        linewidth=1.5
    )
    fig.patches.append(rect)

plt.savefig("Prediction Summary.png", bbox_inches='tight') 

# 5.3 Confusion matrix for the entire test subset
from sklearn.metrics import confusion_matrix

# Use already-computed predictions in `classification`
y_pred = np.argmax(classification, axis=1)
y_true = subset_TestLabels.flatten()

# Generate confusion matrix
cm = confusion_matrix(y_true, y_pred)
label_names = [ClassLabels[i] for i in sorted(ClassLabels.keys())]

fig, ax = plt.subplots(figsize=(8, 6))
# Force the color scale maximum to 100
im = ax.imshow(cm, interpolation='nearest', cmap='Blues', vmin=0, vmax=100)
plt.colorbar(im, ax=ax)

ax.set_xticks(np.arange(len(label_names)))
ax.set_yticks(np.arange(len(label_names)))
ax.set_xticklabels(label_names, rotation=45, ha='right')
ax.set_yticklabels(label_names)
ax.set_xlabel('Predicted label')
ax.set_ylabel('True label')
plt.title('Confusion Matrix for Scene Classification')

# Annotate cells; use threshold based on the forced vmax (100)
thresh = 100 / 2.0
for i in range(cm.shape[0]):
  for j in range(cm.shape[1]):
    color = "white" if cm[i, j] > thresh else "black"
    ax.text(j, i, format(cm[i, j], 'd'), ha="center", va="center", color=color, fontsize=9)

plt.tight_layout()
plt.savefig('Confusion Matrix.png', bbox_inches='tight')

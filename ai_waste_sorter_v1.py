# import PIL #pip install pillow
import pathlib
import tensorflow as tf
import os

from pathlib import Path
# from PIL import UnidentifiedImageError

img_dir = pathlib.Path("screenshot.jpg")

# path = Path("photo").rglob("*.jpg")
# for img_p in path:
#     try:
#         img = PIL.Image.open(img_dir)
#     except PIL.UnidentifiedImageError:
#       print(img_dir)

img = tf.keras.utils.load_img(
    img_dir, target_size=(img_height, img_width)
)

img_array = tf.keras.utils.img_to_array(img)
img_array = tf.expand_dims(img_array, 0) # Create a batch

predictions = model.predict(img_array)
score = tf.nn.softmax(predictions[0])

TF_MODEL_FILE_PATH = 'ai_waste_sorter_v1.tflite' # The default path to the saved TensorFlow Lite model

interpreter = tf.lite.Interpreter(model_path=TF_MODEL_FILE_PATH)

interpreter.get_signature_list()

classify_lite = interpreter.get_signature_runner('serving_default')
classify_lite


predictions_lite = classify_lite(sequential_1_input=img_array)['outputs']
score_lite = tf.nn.softmax(predictions_lite)

print(
    "This image most likely belongs to {} with a {:.2f} percent confidence."
    .format(class_names[np.argmax(score_lite)], 100 * np.max(score_lite))
)

print(np.max(np.abs(predictions - predictions_lite)))
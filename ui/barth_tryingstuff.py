import fastai
from fastai.vision.all import *

import matplotlib.pyplot as plt
import numpy as np
import PIL
import os

#from IPython.display import display, Javascript, Image

from base64 import b64decode, b64encode
import cv2
import io
import html
import time

import pathlib

from pathlib import Path
from PIL import UnidentifiedImageError

import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import serial

from flask import Flask, request, jsonify
from flask_cors import CORS  # Import the CORS module

import pymongo
import sys
from pymongo.mongo_client import MongoClient

from bson import Binary, json_util
from PIL import Image
import io

import serial

import threading
import signal
import subprocess
from werkzeug.serving import run_simple

import requests
# from results import result_recyc
# from multiprocessing import Process, Pipe


# def sendMsg(child_conn):
#     child_conn.send(prediction_str)
#     child_conn.close()

uri = "mongodb+srv://tennercheung:vcJNot9DgpqX918l@cluster0.venlknx.mongodb.net/?retryWrites=true&w=majority"
client = MongoClient(uri)
db = client['waste_captures']
collection = db['random']

url_socketio = 'http://localhost:5000/show_result'



def uploadPicture(prediction, picture_num):
    # Path to text files corresponding to each image
    img_path = "/home/ceg491x-group10/Downloads/CEG4912-Capstone-Project/ui/waste_"+"0"+".jpg"
    text_files = {
        img_path : prediction,
        # 'path/to/your/waste1.jpg': 'Text for image 1',
        # Add more entries as needed
    }

    # Insert images and corresponding text into MongoDB
    for image_path, text in text_files.items():
        with open(image_path, 'rb') as image_file:
            image_binary = Binary(image_file.read())

        # Insert document with image and text
        result = collection.insert_one({'image': image_binary, 'text': text})
        print(f'Image uploaded with ObjectId {result.inserted_id}')

# def sendfromMongoDBtoaArduino():

#     #    ser = serial.Serial(port='/dev/ttyACM0',  baudrate=9600, timeout=.1)
#    #try:
#    #while True:
#         #Récupérer les données depuis MongoDB
#        data_from_mongo = collection.find_one()

#        if data_from_mongo:
#             #Convertir les données en format JSON
#            json_data = json_util.dumps(data_from_mongo)

#             #Envoyer les données à l'Arduino via la connexion série
#            arduino.write(json_data.encode())

#            print(f"Données envoyées à l'Arduino")

#         #Attente entre les envois de données
#        #time.sleep(1)
#        #break
# #    except KeyboardInterrupt:
# #      ser.close()
# #      print("Connexion série fermée.")

def GetLabel(fileName):
    return fileName.split('-')[0]   

def takePicture():
    
#     arduino = serial.Serial(port='/dev/ttyACM0',  baudrate=9600, timeout=.1)
    cam=cv2.VideoCapture(0)
    
    cv2.namedWindow("test", cv2.WINDOW_NORMAL)

    img_counter = 0
        

    
    while True:

        ret, frame = cam.read()
        if not ret:
            print("failed to grab frame")
            break
        cv2.imshow("test", frame)

        k = cv2.waitKey(1)
        # if k%256 == 27:
        #     # ESC pressed
        #     print("Escape hit, closing...")
        #     break
        #elif k%256 == 32:
        if k%256 == 32:     
        # data = arduino.readline().decode('utf-8').rstrip()
        # if (data == "picture"):
        #         time.sleep(2)  
        #         ret, frame = cam.read()

                if ret:
                        img_name = "waste_{}.jpg".format(img_counter)
                        cv2.imwrite(img_name, frame)
                        print("{} written!".format(img_name))
                        img_counter += 1
                        # break

                cam.release()

                cv2.destroyAllWindows()  
                break

    
    

        # return img_counter





def disposeWaste(prediction_str): ## add other using low confidence value (<60%)
    with serial.Serial('/dev/ttyACM0', 9600, timeout=10) as ser:
        waste_bin_name = ""
        if (prediction_str == 'metal' or prediction_str == 'plastic' or prediction_str == 'glass'):
                ser.write(bytes('R\n','utf-8'))
                waste_bin_name+="Recycling bin"

        elif (prediction_str == 'cardboard' or prediction_str == 'paper'):
                ser.write(bytes('P\n','utf-8'))
                waste_bin_name+="Paper bin"

        elif (prediction_str == 'trash'):
                ser.write(bytes('W\n','utf-8'))
                waste_bin_name+="Waste bin"
        print("Disposed of: "+prediction_str+" in: "+waste_bin_name)

        # time.sleep(2)  

data_dir = "/home/ceg491x-group10/Downloads/CEG4912-Capstone-Project/ui"
data_dir = pathlib.Path(data_dir)


#let's grab the first pkl file we can find
modelPath = get_files("/home/ceg491x-group10/Downloads", '.pkl')[0]
modelPath
#modelPath = "export.pkl"
learn_inf = load_learner(modelPath)
prediction_str=""
result = ""

# def updateRes():
#     result = prediction_str
#     return result


while(True):
        img_num = takePicture()
        output = learn_inf.predict(mpimg.imread(get_image_files(data_dir)[0])) #raw prediction
        
        prediction_str = str(output[0])
        data = {"type" : prediction_str}
        response = requests.post(url_socketio, json=data)
        respo = requests.get(url_socketio)
        print (prediction_str)
        print(response.json())
        print(respo)

        uploadPicture(prediction_str,img_num)
        # disposeWaste(prediction_str)

# example_sensor_data = {
#     "distance1": 0 , 
#     "distance2": 20,
#     "distance3": 30,
#     "distance4": 50
# }

# trash_level = {
#     "level1": 100 - example_sensor_data['distance1'], 
#     "level2": 100 - example_sensor_data['distance2'],
#     "level3": 100 - example_sensor_data['distance3'],
#     "level4": 100 - example_sensor_data['distance4']
# }


# models_result = {
#     "type" : prediction_str
# }

# @app.route('/update_distance', methods=['POST'])
# def update_distance():
#     data = request.json if request.is_json else None

#     if data and 'distance' in data:
#         distance = data['distance']
#         # Traitez les données ici (stockage en base de données, fichier, etc.)
#         print("Nouvelle distance mesurée :", distance)
#         return jsonify({'success': True, 'message': 'Données reçues avec succès'})
#     else:
#         return jsonify({'success': False, 'message': 'Données incorrectes'}), 400

# @app.route('/show_result', methods=['GET', 'POST'])
# def show_result():
#     if request.method == 'POST':
#         # Return only the value of the key 'distance' for POST requests
#         return jsonify({'type': models_result['type']})
#     else:
#         # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
#         return f"Le type du waste est : {models_result['type']} "

# @app.route('/show_level1', methods=['GET', 'POST'])
# def show_level1():
#     if request.method == 'POST':
#         # Return only the value of the key 'distance' for POST requests
#         return jsonify({'level1': trash_level['level1']})
#     else:
#         # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
#         return f"La level1 actuelle est : {trash_level['level1']} cm"
    
# @app.route('/show_level2', methods=['GET', 'POST'])
# def show_level2():
#     if request.method == 'POST':
#         # Return only the value of the key 'distance' for POST requests
#         return jsonify({'level2': trash_level['level2']})
#     else:
#         # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
#         return f"La level2 actuelle est : {trash_level['level2']} cm"

# @app.route('/show_level3', methods=['GET', 'POST'])
# def show_level3():
#     if request.method == 'POST':
#         # Return only the value of the key 'distance' for POST requests
#         return jsonify({'level3': trash_level['level3']})
#     else:
#         # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
#         return f"La level3 actuelle est : {trash_level['level3']} cm"

# @app.route('/show_level4', methods=['GET', 'POST'])
# def show_level4():
#     if request.method == 'POST':
#         # Return only the value of the key 'distance' for POST requests
#         return jsonify({'level4': trash_level['level4']})
#     else:
#         # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
#         return f"La level4 actuelle est : {trash_level['level4']} cm"
# if __name__ == '__main__':
#         # run_simple('localhost',5000,app)
#         app.run(debug=True)

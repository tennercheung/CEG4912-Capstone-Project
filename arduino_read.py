import fastai
from fastai.vision.all import *

import matplotlib.pyplot as plt
import numpy as np
import PIL
import os

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

from bson import Binary
from PIL import Image
import io

import serial


def readArduino():

    arduino = serial.Serial(port='/dev/ttyACM0',  baudrate=9600, timeout=.1)
    #x = ""
    #arduino.write(bytes(x,  'utf-8'))
    #time.sleep(0.05)
    while True:
        data = arduino.readline().decode('utf-8').rstrip()
        # if data!="":
        print(data)



readArduino()




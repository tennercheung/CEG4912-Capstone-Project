from flask import Flask, request, jsonify
from flask_cors import CORS  # Import the CORS module

# from multiprocessing import Process,Queue,Pipe
# from ai_waste_sorter_v2 import prediction_str

app = Flask(__name__)
CORS(app)

# Exemple de données du capteur
example_sensor_data = {
    "distance1": 0 , 
    "distance2": 20,
    "distance3": 30,
    "distance4": 50
}

trash_level = {
    "level1": 100 - example_sensor_data['distance1'], 
    "level2": 100 - example_sensor_data['distance2'],
    "level3": 100 - example_sensor_data['distance3'],
    "level4": 100 - example_sensor_data['distance4']
}

# Exemple de resultat du modele
models_result = {
    "type" : "Plastic"
}

@app.route('/update_distance', methods=['POST'])
def update_distance():
    data = request.json if request.is_json else None

    if data and 'distance' in data:
        distance = data['distance']
        # Traitez les données ici (stockage en base de données, fichier, etc.)
        print("Nouvelle distance mesurée :", distance)
        return jsonify({'success': True, 'message': 'Données reçues avec succès'})
    else:
        return jsonify({'success': False, 'message': 'Données incorrectes'}), 400

@app.route('/show_result', methods=['GET', 'POST'])
def show_result():
    if request.method == 'POST':
        # Return only the value of the key 'distance' for POST requests
        return jsonify({'type': models_result['type']})
    else:
        # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
        return f"Le type du waste est : {models_result['type']} "

@app.route('/show_level1', methods=['GET', 'POST'])
def show_level1():
    if request.method == 'POST':
        # Return only the value of the key 'distance' for POST requests
        return jsonify({'level1': trash_level['level1']})
    else:
        # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
        return f"La level1 actuelle est : {trash_level['level1']} cm"
    
@app.route('/show_level2', methods=['GET', 'POST'])
def show_level2():
    if request.method == 'POST':
        # Return only the value of the key 'distance' for POST requests
        return jsonify({'level2': trash_level['level2']})
    else:
        # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
        return f"La level2 actuelle est : {trash_level['level2']} cm"

@app.route('/show_level3', methods=['GET', 'POST'])
def show_level3():
    if request.method == 'POST':
        # Return only the value of the key 'distance' for POST requests
        return jsonify({'level3': trash_level['level3']})
    else:
        # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
        return f"La level3 actuelle est : {trash_level['level3']} cm"

@app.route('/show_level4', methods=['GET', 'POST'])
def show_level4():
    if request.method == 'POST':
        # Return only the value of the key 'distance' for POST requests
        return jsonify({'level4': trash_level['level4']})
    else:
        # Retourne simplement la valeur de distance pour l'afficher dans le navigateur for GET requests
        return f"La level4 actuelle est : {trash_level['level4']} cm"


# def GetLabel(fileName):
#     return fileName.split('-')[0]

if __name__ == '__main__':
    # parent_conn,child_conn = Pipe()
    # p = Process(target=sendMsg,args=(child_conn,))
    # #p2 = Process(target=GetLabel,args=(fileName,))
    # p.start()
    # print("Received:"+str(parent_conn.recv()))

    # print(ai_waste_sorter_v2.prediction_str)
    app.run(debug=True)

    

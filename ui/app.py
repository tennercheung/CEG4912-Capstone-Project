from flask import Flask, jsonify

app = Flask(__name__)

# Exemple de données de résultats de recyclage
recyclage_data = 'plastique'

# Endpoint API pour récupérer les résultats du recyclage
@app.route('/recyclage_resultats', methods=['GET'])
def get_recyclage_resultats():
    return jsonify(recyclage_data)

if __name__ == '__main__':
    app.run(debug=True)
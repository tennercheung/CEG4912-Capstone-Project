import React, { useState, useEffect } from 'react';
import { ProgressBar } from 'react-bootstrap';
import './App.css'; // Import du fichier CSS
import { CircularProgressbar } from 'react-circular-progressbar';
import 'react-circular-progressbar/dist/styles.css';
import axios from 'axios';


function App() {
  const [currentDateTime, setCurrentDateTime] = useState(new Date());
  const [trashLevels, setTrashLevels] = useState([25, 50, 75, 100]);
  const [recyclageResultats, setRecyclageResultats] = useState('');

  useEffect(() => {
    const interval = setInterval(() => {
      setCurrentDateTime(new Date());
    }, 1000);

    return () => clearInterval(interval);
  }, []);

  useEffect(() => {
    // Appel à l'API pour récupérer les résultats du recyclage
    axios.get('http://127.0.0.1:5000//recyclage_resultats')
    
      .then(response => {
        setRecyclageResultats(response.data);
      })
      .catch(error => {
        console.error('Erreur lors de la récupération des résultats du recyclage:', error);
      });
  }, []);

  return (
    <div className="container">
      <div className="header">
        <div className="logo-container">
          <img src="AI SORTER LOGO.png" alt="AI WASTE SORTER" className="logo"/>
        </div>
        <div className="date-time">
          <div className="time-style">
            {currentDateTime.toLocaleTimeString('fr-FR')}
          </div>
          <div className="date-style">
            {currentDateTime.toLocaleDateString('fr-FR')}
          </div>
        </div>
      </div>
      <div className="trash-bins-container">
        {trashLevels.map((level, index) => (
          <div key={index} className="trash-bin">
            <ProgressBar now={level} label={`${level}%`} />
            <CircularProgressbar value={level} text={`${level}%`} />
          </div>
        ))}
      </div>

      <div>
      {/* Autres éléments de votre interface ici */}
      <textarea
        value={recyclageResultats}
        rows={6}
        cols={50}
        readOnly
        placeholder="Résultats du recyclage..."
      />
    </div>
    </div>

  );
}

export default App;

import React, { useState, useEffect } from 'react';
import axios from 'axios';
import Header from './components/Header';
import ProgressBarContainer from './components/ProgressBarContainer';
import RecyclageResultats from './components/RecyclageResultats';
import io from 'socket.io-client';
import './App.css';

function App() {
  const [currentDateTime, setCurrentDateTime] = useState(new Date());
  const [trashLevels, setTrashLevels] = useState([0, 0, 0, 0]);
  const [recyclageResultats, setRecyclageResultats] = useState('');

  useEffect(() => {
    // Fonction pour effectuer la requête POST
    const fetchData = async () => {
      try {
        const [res1, res2, res3, res4, resultRes] = await Promise.all([
          axios.post('http://localhost:5000/show_level1'),
          axios.post('http://localhost:5000/show_level2'),
          axios.post('http://localhost:5000/show_level3'),
          axios.post('http://localhost:5000/show_level4'),
          axios.post('http://localhost:5000/show_result')
        ]);

        const level1 = res1.data.level1;
        const level2 = res2.data.level2;
        const level3 = res3.data.level3;
        const level4 = res4.data.level4;
        const wasteType = resultRes.data.type;

        setRecyclageResultats(wasteType);
        setTrashLevels([level1, level2, level3, level4]);

      } catch (error) {
        console.error('Erreur lors de la récupération des données:', error);
      }
    };

    const dataInterval = setInterval(fetchData, 5000);// every 5 seconds

// Function to update currentDateTime every second
const updateTime = () => {setCurrentDateTime(new Date());};

// Update time every second
const timeInterval = setInterval(updateTime, 1000);


    return () => {clearInterval(dataInterval);
                  clearInterval(timeInterval);}
  }, []);  

  return (
    <>
      <Header currentDateTime={currentDateTime} />
      <RecyclageResultats recyclageResultats={recyclageResultats} />
      <ProgressBarContainer trashLevels={trashLevels} />
    </>
  );
}

export default App;

// function App() {
//   const [currentDateTime, setCurrentDateTime] = useState(new Date());
//   const [trashLevels, setTrashLevels] = useState([0, 0, 0, 0]);
//   const [recyclageResultats, setRecyclageResultats] = useState([]);

//   useEffect(() => {
//     const socket = io('http://localhost:5000');  // Initialisez le socket et connectez-vous à votre serveur

//     // Écoutez l'événement 'nouveaux_resultats' émis par le serveur
//     socket.on('new_result', function(data) {
//        console.log('New results:', data);
//        const r = data.resultat;
//        setRecyclageResultats(r); // Mettez à jour les résultats de recyclage dans l'état
//     });

//     // Fonction pour effectuer la requête POST et récupérer les données initiales
//     const fetchData = async () => {
//       try {
//         const [res1, res2, res3, res4] = await Promise.all([
//           axios.post('http://localhost:5000/show_level1'),
//           axios.post('http://localhost:5000/show_level2'),
//           axios.post('http://localhost:5000/show_level3'),
//           axios.post('http://localhost:5000/show_level4')
//         ]);

//         const level1 = res1.data.level1;
//         const level2 = res2.data.level2;
//         const level3 = res3.data.level3;
//         const level4 = res4.data.level4;

//         setTrashLevels([level1, level2, level3, level4]);
//       } catch (error) {
//         console.error('Erreur lors de la récupération des données :', error);
//       }
//     };

//     const dataInterval = setInterval(fetchData, 5000); // Récupérez les données initiales toutes les 5 secondes

//     // Fonction pour mettre à jour currentDateTime toutes les secondes
//     const updateTime = () => { setCurrentDateTime(new Date()); };

//     // Mettez à jour l'heure toutes les secondes
//     const timeInterval = setInterval(updateTime, 1000);

//     return () => {
//       clearInterval(dataInterval);
//       clearInterval(timeInterval);
//       // socket.disconnect();  // Déconnectez-vous du socket lors du démontage du composant
//     };
//   }, []);

//   return (
//     <>
//       <Header currentDateTime={currentDateTime} />
//       <RecyclageResultats recyclageResultats={recyclageResultats} />
//       <ProgressBarContainer trashLevels={trashLevels} />
//     </>
//   );
// }

// export default App;

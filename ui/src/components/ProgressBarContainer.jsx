import React from 'react';
import { ProgressBar } from 'react-bootstrap';
import { CircularProgressbar } from 'react-circular-progressbar';
import 'react-circular-progressbar/dist/styles.css';

function ProgressBarContainer({ trashLevels }) {
    const binTitles = ['Bin 1', 'Bin 2', 'Bin 3', 'Bin 4']; // Add more titles if needed

  return (
    <div className="trash-bins-container">
      {trashLevels.map((level, index) => (
        <div key={index} className="trash-bin">
          {/* <ProgressBar now={level} label={`${level}%`} /> */}
          <CircularProgressbar value={level} text={`${level}%`} />
          <div className="bin-title">{binTitles[index]}</div>
          {level > 90 && <div className="bin-message">Bin is full!</div>}
        </div>
      ))}
    </div>
  );
}

export default ProgressBarContainer;
import React, { useState, useEffect } from 'react';

function RecyclageResultats({ recyclageResultats }) {
  const [displayedResult, setDisplayedResult] = useState(recyclageResultats);

  useEffect(() => {
    setDisplayedResult(recyclageResultats); // Set the initial value

    const timer = setTimeout(() => {
      setDisplayedResult("Model's result..."); // Revert to placeholder after 15 seconds
    }, 15000); // 15 seconds in milliseconds

    return () => clearTimeout(timer); // Clear the timer on component unmount
  }, [recyclageResultats]);

  return (
    <div className="result-container">
      <h2>Your waste is:</h2>
      <div className="result-box">
        <div className="result-text">
          {displayedResult}
        </div>
      </div>
    </div>
  );
}

export default RecyclageResultats;

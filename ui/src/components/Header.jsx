import React from 'react';

function Header({ currentDateTime }) {
  return (
    <div className="header">
      <div className="logo-container">
        <img src="AI SORTER LOGO.png" alt="AI WASTE SORTER" className="logo" />
      </div>
      <div className="date-time">
        <div className="time-style" style={{ fontSize: '30px' }}>{currentDateTime.toLocaleTimeString('fr-FR')}</div>
        <div className="date-style" style={{ fontSize: '30px' }}>{currentDateTime.toLocaleDateString('fr-FR')}</div>
      </div>
    </div>
  );
}

export default Header;

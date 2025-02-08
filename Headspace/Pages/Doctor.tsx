import Player from "./Player"
import {useState} from 'react'
import "./Doctor.css"
const Doctor = () => {

  const [show, setShow] = useState(false);
  const [val, setValue] = useState('');

  const handleNote = () => {
    console.log(val);
  }


  const showPlayer = () => {
    if (show)
      setShow(false);
    else
      setShow(true);
  }

  return (
    <div className="Doctor">
      <h1>DOCTOR</h1>
      <h2>Pick a player</h2>
      <button className="playerNameBtn" onClick={showPlayer}> L9 Ligma </button>
      {show && (<Player/>)}

      <p>Notes</p>
      <textarea value={val} rows={4} cols={50} onChange={(e)=>setValue(e.target.value)}></textarea>
      <button className="submitBtn" onClick={handleNote}>Submit</button>

    </div>
  )
}

export default Doctor
import Player from "./Player"
import {useState} from 'react'
import { useLocalStorage } from "../Utils/useLocalStorage"
import "./Doctor.css"
const Doctor = () => {

  const [show, setShow] = useState(false);
  const [note, setNote] = useState('');

  const {setItem} = useLocalStorage('note');

  const showPlayer = () => {
    if (show)
      setShow(false);
    else
      setShow(true);
  }


  const callBoth = () => {

    setItem(note);
    setNote("");
  }

  return (
    <div className="Doctor">
      <h1>DOCTOR</h1>
      <h2>Pick a player</h2>
      <button className="playerNameBtn" onClick={showPlayer}> L9 Ligma </button>
      {show && (<Player/>)}

      <p>Notes</p>
      <textarea value={note} rows={4} cols={50} onChange={(e)=>setNote(e.target.value)}></textarea>
      <button className="submitBtn" onClick={callBoth}>Submit</button>

    </div>
  )
}

export default Doctor
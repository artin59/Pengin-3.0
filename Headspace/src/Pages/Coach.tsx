import { useLocalStorage } from "../Utils/useLocalStorage"
import { useState } from "react"
import Player from "./Player"
import "./Coach.css"

const Coach = () => {


  const [show, setShow] = useState(false);
  const [note, setNote] = useState('');

  const {getItem} = useLocalStorage("note");

  const showPlayer = () => {
    if (show)
      setShow(false);
    else
      setShow(true);
  }

  const showDoctorNote = () => {
    
    const savedNote = getItem();
    setNote(savedNote || "No doctor's note found")

  }

  return (

    <div className="Coach">

      <h1>Coach</h1>
      <h2>Pick a player</h2>
      <button className="playerNameBtn" onClick={showPlayer}> L9 Ligma </button>
      {show && (<Player/>)}
      <button className="submitBtn" onClick={showDoctorNote}>Get Doctor's Note</button>
      {note && 
      <div className="DoctorsNote">
        <p>{note}</p>
      </div>}

    </div>

  )

}

export default Coach
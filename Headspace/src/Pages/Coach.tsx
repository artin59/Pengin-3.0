import { useLocalStorage } from "../Utils/useLocalStorage"
import { useState } from "react"
import Player from "./Player"
import "./Coach.css"

const Coach = () => {


  const [show, setShow] = useState(false);
  const [note, setNote] = useState('');
  const [showButton, setButton] = useState(false);

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

  const showDoctorButton = () => {
    if (showButton)
      setButton(false);
    else
      setButton(true);
  }

  const showBoth = () => {
    showPlayer();
    showDoctorButton();
  }

  return (

    <div className="Coach">

      <h1>Coach</h1>
      <h2>Pick a player</h2>
      <button className="playerNameBtn" onClick={showBoth}> L9 Ligma </button>
      {show && (<Player/>)}

      {showButton && 
      <div>
        <button className="submitBtn" onClick={showDoctorNote}>Get Doctor's Note</button>
        {note && 
        <div className="DoctorsNote">
          <p>{note}</p>
        </div>}
      </div>}
    </div>

  )

}

export default Coach
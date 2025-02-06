import LoginButton from "../Components/LoginButton"
import LogoutButton from "../Components/LogoutButton"
import Profile from "../Components/Profile"
import Coach from "../Pages/Coach"
import Player from "../Pages/Player"
import { BrowserRouter as Router, Routes, Route, Navigate, BrowserRouter } from "react-router-dom";
import './App.css'
import { useAuth0 } from "@auth0/auth0-react"

function App() {

  const { isAuthenticated} = useAuth0();

  return (
      <BrowserRouter>
        <div>
        {isAuthenticated ? <LogoutButton /> : <LoginButton />}
        <Routes>
          <Route path="/" element={ <Profile/>} />
          <Route path="/coach" element={<Coach />} />
          <Route path="/player" element={<Player />} />
        </Routes>
      </div>
    </BrowserRouter>
  )
}

export default App

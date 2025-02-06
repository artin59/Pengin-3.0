import LoginButton from "./LoginButton"
import LogoutButton from "./LogoutButton"
import "./Navbar.css"

const NavBar = () => {
  return (
    <nav className="navbar">
        <a href="/" className="title">HeadSpace</a>
        <div className="logging">
        <LoginButton/>
        <LogoutButton/>
        </div>
    </nav>
)
}

export default NavBar
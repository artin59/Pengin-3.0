import React, { useEffect } from "react";
import { useNavigate } from "react-router-dom";
import { useAuth0 } from "@auth0/auth0-react";

const Profile = () => {
  const { user, isAuthenticated, isLoading } = useAuth0();
  const navigate = useNavigate();

  if (isLoading) {
    return <div>Loading ...</div>;
  }

  useEffect(() => {
    if (!isLoading && isAuthenticated && user) {

        switch(user.email) {
            case "artinkiany59@gmail.com":
                navigate("/coach");
                break;
            case "l9ligma@gmail.com":
                navigate("/player");
                break;
            default:
                navigate("/");
                break;
        }
    }
  }, [user, isAuthenticated, isLoading, navigate]);

};

export default Profile;
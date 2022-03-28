import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom'
import Home from '../../pages'
import SignInPage from '../../pages/signIn'
import SignUpPage from '../../pages/signUp'
import User from '../../pages/user'
import SettingsPage from '../../pages/settings'
import CreateAccountPage from '../../pages/createAccount'
import DashboardPage from '../../pages/dashboard'
import useToken from '../UseToken/useToken'
import NotFound from '../Error/404'

/**
 * 
 * Sets up routes for all the pages in the app
 */
const AppRoutes = () => {

  // Call the custom token hook useToken
  const { token, setToken }= useToken();

  return <>
    <Router>
      <Routes>

        <Route path='/' element={<Home />} />
        <Route path='/signUp' element={<SignUpPage />} />
        <Route path='/404' element={<NotFound />} />
        
        
        {
        // If the token is  not present then redirect to SignInPage 
        !token && (<Route path='/signIn' element={<SignInPage setToken={setToken} />} />)
        }
        
        
        {
        // If token is present then give access to these pages
        token && (
          <>
            <Route path='/user' element={<User />} />
            <Route path='/settings' element={<SettingsPage />} />
            <Route path='/createAccount' element={<CreateAccountPage />} />
            <Route path='/dashboard' element={<DashboardPage />} />
          </>
        )}
        <Route path="*" element={<Navigate replace to={ token ? 'dashboard' : '/signIn'}/>}/>      
      </Routes>
    </Router>
  </>
}

export default AppRoutes
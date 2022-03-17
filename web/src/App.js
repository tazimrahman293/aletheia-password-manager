import './App.css';
import {BrowserRouter as Router, Routes, Route} from 'react-router-dom'
import Home from './pages';
import SignInPage from './pages/signIn';
import SignUpPage from './pages/signUp';
import User from './pages/user';
import SettingsPage from './pages/settings';
import DashboardPage from './pages/dashboard';

/**
 * 
 * Sets up routes for all the pages in the app
 */
function App() {
  return (
    <Router>
      <Routes>
        <Route path='/' element={<Home/>}/>
        <Route path='/signIn' element={<SignInPage/>}/>
        <Route path='/signUp' element={<SignUpPage/>}/>
        <Route path='/user' element={<User/>}/>
        <Route path='/settings' element={<SettingsPage/>}/>
        <Route path='/dashboard' element={<DashboardPage/>}/>
      </Routes>
    </Router>
  );
}

export default App;

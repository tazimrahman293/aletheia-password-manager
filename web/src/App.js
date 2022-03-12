import './App.css';
import {BrowserRouter as Router, Routes, Route} from 'react-router-dom'
import Home from './pages';
import SignInPage from './pages/signIn';
import SignUpPage from './pages/signUp';

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

      </Routes>
    </Router>
  );
}

export default App;

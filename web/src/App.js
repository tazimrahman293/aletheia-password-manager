import './App.css';
import {BrowserRouter as Router, Routes, Route} from 'react-router-dom'
import Home from './pages';
import SignInPage from './pages/signIn';

function App() {
  return (
    <Router>
      <Routes>
        <Route path='/' element={<Home/>}/>
        <Route path='/signIn' element={<SignInPage/>}/>

      </Routes>
    </Router>
  );
}

export default App;

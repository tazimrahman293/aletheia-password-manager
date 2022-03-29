import axios from 'axios';

/**
 * This is the api instance
 */
const instance = axios.create({
    baseURL: 'http://localhost:8089'

});

export default instance;
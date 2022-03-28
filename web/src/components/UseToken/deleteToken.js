export default function deleteToken(){
    localStorage.removeItem('token')
    window.location.reload(false);
}
import * as React from 'react';
import Box from '@mui/material/Box';
import Button from '@mui/material/Button';
import Typography from '@mui/material/Typography';
import Modal from '@mui/material/Modal';
import axios from '../api/axios';
import { useState, useEffect } from 'react';

const style = {
  position: 'absolute',
  top: '50%',
  left: '50%',
  transform: 'translate(-50%, -50%)',
  width: 400,
  bgcolor: 'background.paper',
  border: '2px solid #000',
  boxShadow: 24,
  p: 4,
};

export default function BasicModal() {

  const [password, setPassword] = useState()


  const generatePassword = () => {
    axios
    .put('/account/key?account=1', {
      "pk": 1,
      "random": true,
      "length": 16,
      "lowers": true,
      "uppers": true,
      "numbers": true,
      "specials": true
    })
    // .then((response) => {setPassword(response(response['key'])))
    //   console.log(response['key'])})
    // .then((data) => {setPassword(data)
    // console.log(data.key)})
    .catch(error => {
      console.log(error)
    })
  } 
  useEffect(() => {
    axios
    .get('/account/key?account=1')
    .then((response) => {setPassword((response.data['key']))
    console.log(response.data['key'])})
    // .then((data) => {setPassword(data)
    // console.log(data)})
    .catch(error => {
      console.log(error)
    })
  })

  
  const [open, setOpen] = React.useState(false);
  const handleOpen = () => setOpen(true);
  const handleClose = () => setOpen(false);

  return (
    <div>
      <Button style={{
          background:'#F56300',
          border: '2px solid #fff',
          color: '#fff',
          borderRadius: '50px',
          padding: '12px 30px',
        }} onClick={handleOpen}>Generate a new Password </Button>
      <Modal
        open={open}
        onClose={handleClose}
        aria-labelledby="modal-modal-title"
        aria-describedby="modal-modal-description"
      >
        <Box sx={style}>
          <Typography id="modal-modal-title" variant="h6" component="h2">
          <Button onClick={generatePassword}>Generate a new Password </Button>
          </Typography>
          <Typography id="modal-modal-description" sx={{ mt: 2 }}>
            {password}
          </Typography>
        </Box>
      </Modal>
    </div>
  );
}

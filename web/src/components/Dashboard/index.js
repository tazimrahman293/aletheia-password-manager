//TODO: Implement the dashboard component with data grid from MUI library

import React, { useState, useEffect } from 'react';
import { forwardRef } from 'react';
import Avatar from 'react-avatar';
import MaterialTable from 'material-table';
import AddBox from '@material-ui/icons/AddBox';
import ArrowDownward from '@material-ui/icons/ArrowDownward';
import Check from '@material-ui/icons/Check';
import ChevronLeft from '@material-ui/icons/ChevronLeft';
import ChevronRight from '@material-ui/icons/ChevronRight';
import Clear from '@material-ui/icons/Clear';
import DeleteOutline from '@material-ui/icons/DeleteOutline';
import Edit from '@material-ui/icons/Edit';
import FilterList from '@material-ui/icons/FilterList';
import FirstPage from '@material-ui/icons/FirstPage';
import LastPage from '@material-ui/icons/LastPage';
import Remove from '@material-ui/icons/Remove';
import SaveAlt from '@material-ui/icons/SaveAlt';
import Search from '@material-ui/icons/Search';
import ViewColumn from '@material-ui/icons/ViewColumn';
import Alert from '@material-ui/lab/Alert';
import { Typography } from '@mui/material';
import { Box } from '@mui/system';
import useToken from '../UseToken/useToken';
import axios from '../../api/axios';
import Demo from '../demo'

const tableIcons = {
  Add: forwardRef((props, ref) => <AddBox {...props} ref={ref} />),
  Check: forwardRef((props, ref) => <Check {...props} ref={ref} />),
  Clear: forwardRef((props, ref) => <Clear {...props} ref={ref} />),
  Delete: forwardRef((props, ref) => <DeleteOutline {...props} ref={ref} />),
  DetailPanel: forwardRef((props, ref) => <ChevronRight {...props} ref={ref} />),
  Edit: forwardRef((props, ref) => <Edit {...props} ref={ref} />),
  Export: forwardRef((props, ref) => <SaveAlt {...props} ref={ref} />),
  Filter: forwardRef((props, ref) => <FilterList {...props} ref={ref} />),
  FirstPage: forwardRef((props, ref) => <FirstPage {...props} ref={ref} />),
  LastPage: forwardRef((props, ref) => <LastPage {...props} ref={ref} />),
  NextPage: forwardRef((props, ref) => <ChevronRight {...props} ref={ref} />),
  PreviousPage: forwardRef((props, ref) => <ChevronLeft {...props} ref={ref} />),
  ResetSearch: forwardRef((props, ref) => <Clear {...props} ref={ref} />),
  Search: forwardRef((props, ref) => <Search {...props} ref={ref} />),
  SortArrow: forwardRef((props, ref) => <ArrowDownward {...props} ref={ref} />),
  ThirdStateCheck: forwardRef((props, ref) => <Remove {...props} ref={ref} />),
  ViewColumn: forwardRef((props, ref) => <ViewColumn {...props} ref={ref} />)
};

export default function Dashboard() {

  const columns = [
    { field: 'pk', title: 'Id', editable: false },
    { title: "Icon", render: rowData => <Avatar maxInitials={1} size={40} round={true} name={rowData === undefined ? " " : rowData.label} /> },
    { field: 'label', title: 'Account Name' },
    { field: 'username', title: 'User Name' },
    { field: 'url', title: 'Url' },
    { field: 'password', title: 'Password' }
  ]

  const { token } = useToken();
  const url = "/account?user=" + token.pk

  const [data, setData] = useState([])

  //for error handling
  const [iserror, setIserror] = useState(false)
  const [errorMessages, setErrorMessages] = useState([])


  useEffect(() => {
    axios
      .get(url, { headers: { 'Content-Type': 'application/json', crossDomain: true } })
      .then((response) => (response.data))
      .then((data) => { setData(data) })
      .catch(error => {
        // setErrorMessages(["Cannot load user data"])
        // setIserror(true)
        console.log(error)
      });
  }, [url])

  const handleRowUpdate = (newData, oldData, resolve) => {
    //validation
    let errorList = []
    if (newData.label === "") {
      errorList.push("Please enter a label")
    }
    if (newData.username === "") {
      errorList.push("Please enter a username")
    }
    if (newData.url === "") {
      errorList.push("Please enter a url")
    }

    if (errorList.length < 1) {
      axios({
        url: "/account",
        method:"PATCH",
        data: {
        "pk": newData.pk,
        "url": newData.url,
        "label": newData.label,
        "username": newData.username}
      })
        .then(res => {
          const dataUpdate = [...data];
          const index = oldData.tableData.id;
          dataUpdate[index] = newData;
          setData([...dataUpdate]);
          resolve()
          setIserror(false)
          setErrorMessages([])
        })
        .catch(error => {
          setErrorMessages(["Update failed! Server error"])
          setIserror(true)
          resolve()

        })
    } else {
      setErrorMessages(errorList)
      setIserror(true)
      resolve()

    }

  }

  const handleRowAdd = (newData, resolve) => {
    let errorList = []
    if (newData.label === "") {
      errorList.push("Please enter a label")
    }
    if (newData.username === "") {
      errorList.push("Please enter a username")
    }
    if (newData.url === "") {
      errorList.push("Please enter a url")
    }
    if (newData.password === "") {
      errorList.push("Please enter a password")
    }

    if (errorList.length < 1) { //no error
      axios.post("/account", JSON.stringify({
        "pk": 1,
        "username": newData.username,
        "label": newData.label,
        "url": newData.url,
        "password": newData.password,
        "created": 0,
        "lastAccessed": 0,
        "lastModified": 0,
        "expiry": 0,
        "userID": token.pk

      }))
        .then(res => {
          let dataToAdd = [...data];
          dataToAdd.push(newData);
          setData(dataToAdd);
          resolve()
          window.location.reload();
          setErrorMessages([])
          setIserror(false)
        })
        .catch(error => {
          setErrorMessages(["Cannot add data. Server error!"])
          setIserror(true)
          resolve()
        })
    } else {
      setErrorMessages(errorList)
      setIserror(true)
      resolve()
    }


  }

  const handleRowDelete = (oldData, resolve) => {
    const id = JSON.stringify({ pk: oldData.pk });
    console.log(id)
    
    axios
      ({url : "/account",
        method: 'DELETE',
        data: id}
      )
      .then(res => {
        const dataDelete = [...data];
        const index = oldData.tableData.pk;
        dataDelete.splice(index, 1);
        setData([...dataDelete]);
        resolve()
      })
      .catch(error => {
        setErrorMessages(["Delete failed! Server error"])
        setIserror(true)
        resolve()
      })
  }

  return (

    <Box
      sx={{
        display: 'flex',
        flex: '1 1 auto',
        flexDirection: 'column',
        width: '100%',
        padding: '25vh 20vw'

      }}
    >
      <Typography
        color="#F56300"
        sx={{ mb: 3 }}
        variant="h4"
      >
         Dashboard  
      </Typography>
      <div>
        {iserror &&
          <Alert severity="error">
            {errorMessages.map((msg, i) => {
              return <div key={i}>{msg}</div>
            })}
          </Alert>
        }
      </div>
      <MaterialTable
        title={<Demo/>}
        columns={columns}   
        data={data}
        icons={tableIcons}
        editable={{
          onRowUpdate: (newData, oldData) =>
            new Promise((resolve) => {
              handleRowUpdate(newData, oldData, resolve);
            }),
          onRowAdd: (newData) =>
            new Promise((resolve) => {
              handleRowAdd(newData, resolve)
            }),
          onRowDelete: (oldData) =>
            new Promise((resolve) => {
              handleRowDelete(oldData, resolve)
            }),
        }}
      />
    </Box>

  );
}
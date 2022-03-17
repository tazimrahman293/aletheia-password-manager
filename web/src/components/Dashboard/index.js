//TODO: Implement the dashboard component with data grid from MUI library

import * as React from 'react';
import { DataGrid } from '@mui/x-data-grid';
import { Grid, Typography } from '@mui/material';
import { Box } from '@mui/system';

const columns = [
  // { field: 'id', headerName: 'ID', width: 90 },
  {
    field: 'label',
    headerName: 'Account Name',
    width: 150,
    editable: true,
  },
  {
    field: 'userName',
    headerName: 'User Name',
    width: 150,
    editable: true,
  },
  {
    field: 'url',
    headerName: 'Url',
    // type: 'number',
    width: 180,
    editable: true,
  },
  {
    field: 'password',
    headerName: 'Password',
    type: 'password',
    width: 120,
    // editable: true,
  }
];

const rows = [
  { id: 1, label: 'Netflix', userName: 'Jon', url: 'netflix.com', password: 'Password' },
  { id: 2, label: 'Facebook', userName: 'Jon', url: 'Facebook.com', password: 'Password' },
  { id: 3, label: 'Yahoo', userName: 'Jon', url: 'Yahoo.com', password: 'Password' },
  { id: 4, label: 'Twitter', userName: 'Jon', url: 'Twitter.com', password: 'Password' },
  { id: 5, label: 'Playstation', userName: 'Jon', url: 'Playstation.com', password: 'Password' }
];

export default function Dashboard() {
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

      <div style={{ height: 500, width: '100%' }}>
        <DataGrid
          rows={rows}
          columns={columns}
          pageSize={10}
          rowsPerPageOptions={[10]}
          checkboxSelection
          disableSelectionOnClick
        />
      </div>
    </Box>

  );
}
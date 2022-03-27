//TODO: Implement the settings component 
import React, { useState } from 'react'
import { Box, Button, Card, CardContent, CardHeader, Divider,  TextField} from '@mui/material';
import { Column1, Column2, DataContainer, DataRow, DataWrapper, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements';

const Settings = (props) => {
    const [values, setValues] = useState({
        currentPassword: '',
        newPassword: '',
        confirmPassword: ''
      });


    // TODO: Convert the form into an formik element.
      const handleChange = (event) => {
        setValues({
          ...values,
          [event.target.name]: event.target.value
        });
      };
    
    //TODO: Create API request of type PATCH to update user details
    return (
        <>
            <DataContainer lightBg='true' id='form'>
                <DataWrapper>
                    <DataRow imgStart='true'>
                        <Column1>
                            <TextWrapper>
                                <form {...props}>
                                    <Card>
                                        <CardHeader
                                            subheader="Update password"
                                            title="Password"
                                        />
                                        <Divider />
                                        <CardContent>
                                            <TextField
                                                fullWidth
                                                label="Current Password"
                                                margin="normal"
                                                name="currentPassword"
                                                onChange={handleChange}
                                                type="password"
                                                value={values.currentPassword}
                                                variant="outlined"
                                            />
                                            <TextField
                                                fullWidth
                                                label="New Password"
                                                margin="normal"
                                                name="newPassword"
                                                onChange={handleChange}
                                                type="password"
                                                value={values.newPassword}
                                                variant="outlined"
                                            />
                                            <TextField
                                                fullWidth
                                                label="Confirm password"
                                                margin="normal"
                                                name="confirmPassword"
                                                onChange={handleChange}
                                                type="password"
                                                value={values.confirmPassword}
                                                variant="outlined"
                                            />
                                        </CardContent>
                                        <Divider />
                                        <Box
                                            sx={{
                                                display: 'flex',
                                                justifyContent: 'flex-end',
                                                p: 2
                                            }}
                                        >
                                            <Button
                                                color="primary"
                                                variant="contained"
                                            >
                                                Update
                                            </Button>
                                        </Box>
                                    </Card>
                                </form>
                            </TextWrapper>
                        </Column1>
                        <Column2>
                            <ImgWrap>
                                <Img src={require('./../../images/svg1.svg').default} alt='logo' />
                            </ImgWrap>
                        </Column2>
                    </DataRow>
                </DataWrapper>
            </DataContainer>
        </>
    )
}

export default Settings

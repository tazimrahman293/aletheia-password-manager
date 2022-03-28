//TODO: Implement the settings component 
import React from 'react'
import { Box, Button, Card, CardContent, CardHeader, Divider,  TextField} from '@mui/material';
import { Column1, Column2, DataContainer, DataRow, DataWrapper, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements';
import { useFormik} from 'formik';
import * as yup from "yup";
const Settings = () => {

      const formik = useFormik({
          initialValues: {
              currentPassword: '',
              newPassword: '',
              confirmPassword: ''
          },
          validateOnChange:false,
          validationSchema: yup.object({
            currentPassword: yup.string().password().required().max(255),
            newPassword: yup.string().password().required().max(255),
            confirmPassword: yup.string().oneOf([yup.ref('password'), null], "Passwords must match")
          }),

          onSubmit: values => {

          }

      })
    
    //TODO: Create API request of type PATCH to update user details
    return (
        <>
            <DataContainer lightBg='true' id='form'>
                <DataWrapper>
                    <DataRow imgStart='true'>
                        <Column1>
                            <TextWrapper>
                                <form onSubmit={formik.handleSubmit}>
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
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                type="password"
                                                value={formik.values.currentPassword}
                                                variant="outlined"
                                            />
                                            <TextField
                                                fullWidth
                                                label="New Password"
                                                margin="normal"
                                                name="newPassword"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                type="password"
                                                value={formik.values.newPassword}
                                                variant="outlined"
                                            />
                                            <TextField
                                                fullWidth
                                                label="Confirm password"
                                                margin="normal"
                                                name="confirmPassword"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                type="password"
                                                value={formik.values.confirmPassword}
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
                                               style={{ backgroundColor: '#F56300' }}
                                               disabled={formik.isSubmitting}
                                               fullWidth
                                               size="large"
                                               type="submit"
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

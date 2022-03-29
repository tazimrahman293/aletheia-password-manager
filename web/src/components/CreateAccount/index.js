import React from 'react';
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements';
import * as yup from "yup";
import { Link as LinkRouter } from 'react-router-dom';
import YupPassword from 'yup-password';
import axios from './../../api/axios';
import { useFormik } from 'formik';
import { Box, Button, Container, TextField, Typography } from '@mui/material';
import { Nav, NavContainer } from '../Navbar/NavbarElements'
import { Icon } from './../SignIn/SigninElements'
YupPassword(yup)


// URL for user requests
const accountUrl = '/account';


/**
 * 
 * @returns signUp Page
 */
const CreateAccount = () => {

    const formik = useFormik({
        initialValues: {
            label: '',
            url: '',
            userName: '',
            password: '',

        },
        validateOnChange: false,
        validationSchema: yup.object({
            label: yup.string().required().max(255),
            url: yup.string().required().max(255),
            userName: yup.string().required().max(255),
            password: yup.string().password().required().max(255),
        }),
        // function for submission event handling
        // initializes api requests
        onSubmit: values => {

            alert(JSON.stringify({
                'pk': 1,
                'username': values.userName,
                'label': values.label,
                'url': values.url,
                'keyHash': values.password
            }, null, 2));

            // post request to register new user
            axios
                .post(accountUrl, JSON.stringify({
                    'pk': 1,
                    'username': values.userName,
                    'label': values.label,
                    'url': values.url,
                    'keyHash': values.password,
                    "created": 0,
                    "lastAccessed": 0,
                    "lastModified": 0,
                    "expiry": 0,
                    "userID": 1

                }),// TODO shift headers into AXIOS api
                    { headers: { 'Content-Type': 'application/json', crossDomain: true } }
                )
                .then(response => { console.log(response.data) })
                .catch(error => { console.log(error.data) });

            
        }
    });


    return (
        <>
            <Nav>
                <NavContainer>
                    <Icon to='/'>Aletheia</Icon>
                </NavContainer>
            </Nav>

            <DataContainer lightBg={true} id='form'>
                <DataWrapper>
                    <DataRow imgStart='true'>
                        <Column1>
                            <TextWrapper>
                                <Box
                                    component="main"
                                    sx={{
                                        alignItems: 'center',
                                        display: 'flex',
                                        flexGrow: 1,
                                        minHeight: '100%'
                                    }}
                                >
                                    <Container maxWidth="sm">
                                        <form onSubmit={formik.handleSubmit}>
                                            <Box sx={{ my: 3 }}>
                                                <Typography
                                                    color="textPrimary"
                                                    variant="h4"
                                                >
                                                    Create a new account
                                                </Typography>
                                                <Typography
                                                    color="textSecondary"
                                                    gutterBottom
                                                    variant="body2"
                                                >
                                                    Fill the information to create a new account
                                                </Typography>
                                            </Box>
                                            <TextField
                                                error={Boolean(formik.touched.label && formik.errors.label)}
                                                fullWidth
                                                helperText={formik.touched.label && formik.errors.label}
                                                label="Label"
                                                margin="normal"
                                                name="label"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                value={formik.values.label}
                                                variant="outlined"
                                            />
                                            <TextField
                                                error={Boolean(formik.touched.url && formik.errors.url)}
                                                fullWidth
                                                helperText={formik.touched.url && formik.errors.url}
                                                label="Url"
                                                margin="normal"
                                                name="url"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                value={formik.values.url}
                                                variant="outlined"
                                            />
                                            <TextField
                                                error={Boolean(formik.touched.userName && formik.errors.userName)}
                                                fullWidth
                                                helperText={formik.touched.userName && formik.errors.userName}
                                                label="User Name"
                                                margin="normal"
                                                name="userName"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                value={formik.values.userName}
                                                variant="outlined"
                                            />
                                            <TextField
                                                error={Boolean(formik.touched.password && formik.errors.password)}
                                                fullWidth
                                                helperText={formik.touched.password && formik.errors.password}
                                                label="Password"
                                                margin="normal"
                                                name="password"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                type="password"
                                                value={formik.values.password}
                                                variant="outlined"
                                            />
                                        


                                            <Box sx={{ py: 2 }}>
                                                <Button
                                                    style={{ backgroundColor: '#F56300' }}
                                                    disabled={formik.isSubmitting}
                                                    fullWidth
                                                    size="large"
                                                    type="submit"
                                                    variant="contained"
                                                >
                                                    Create Account
                                                </Button>
                                            </Box>
                                            <Typography
                                                color="textSecondary"
                                                variant="body2"
                                            >
                                                Have an account?
                                                {' '}

                                                <LinkRouter to="/dashboard" id="RouterNavLink" style={{ color: '#F56300' }}>
                                                    Go to Dashboard
                                                </LinkRouter>
                                            </Typography>
                                        </form>
                                    </Container>
                                </Box>
                            </TextWrapper>
                        </Column1>
                        <Column2>
                            <ImgWrap>
                                <Img src={require('../../images/svg6.svg').default} alt='logo' />
                            </ImgWrap>
                        </Column2>
                    </DataRow>
                </DataWrapper>
            </DataContainer>
        </>
    )
}

export default CreateAccount

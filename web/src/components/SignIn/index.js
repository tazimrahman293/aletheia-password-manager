import React from 'react'
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements'
import { useFormik } from 'formik';
import * as yup from "yup";
import axios from './../../api/axios';
import { Box, Button, Container, TextField, Typography } from '@mui/material';
import { Link as LinkRouter } from 'react-router-dom';
import { Nav, NavContainer } from '../Navbar/NavbarElements';
import { Icon } from './../SignIn/SigninElements';
import PropTypes from 'prop-types';
import { Navigate } from 'react-router';

// URL for user requests
const userUrl = '/login';

/**
 * 
 * @returns SignIn Page
 */
export default function SignIn({ setToken }) {

    const formik = useFormik({
        initialValues: {
            userName: '',
            password: ''
        },
        validateOnChange: false,
        validationSchema: yup.object({
            // TODO: change it to UserName
            userName: yup.string().required().max(255),
            // userName: yup.number().required().max(255),
            password: yup.string().required().max(255)
        }),
        // function for submission event handling
        // initializes api requests
        onSubmit: values => {

            // post request to register new user
            axios
                .post(userUrl, JSON.stringify({
                    // TODO: pk for now, need API support for username
                    'username': values.userName,
                    'key': values.password
                }),
                    { headers: { 'Content-Type': 'application/json', crossDomain: true } }
                )
                .then(response => {
                    // on Success pass the response as a token to setToken Function
                    const token = response.data
                    console.log(token)
                    setToken(token);
                })
                .catch(error => { 
                    // console.log(error.data)
                    if (!error.request){
                        <Navigate replace to='/500'/>
                    } else {
                        console.log(error.data)
                    }
                });
            console.log(JSON.stringify(values, null, 2))
        }
    });

    return (
        <>
            <Nav>
                <NavContainer>
                    <Icon to='/'>Aletheia</Icon>
                </NavContainer>
            </Nav>

            <DataContainer lightBg='true' id='form'>
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
                                                    Sign in to your account
                                                </Typography>
                                                <Typography
                                                    color="textSecondary"
                                                    gutterBottom
                                                    variant="body2"
                                                >
                                                    Fill the information to sign in
                                                </Typography>
                                            </Box>

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
                                                    Sign In
                                                </Button>
                                            </Box>
                                            <Typography
                                                color="textSecondary"
                                                variant="body2"
                                            >
                                                Don't have an account?
                                                {' '}

                                                <LinkRouter to="/signUp" id="RouterNavLink" style={{ color: '#F56300' }}>
                                                    Sign Up
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

SignIn.propTypes = {
    setUser: PropTypes.func.isRequired
};


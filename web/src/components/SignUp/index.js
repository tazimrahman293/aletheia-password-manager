import React, { useState } from 'react';
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements';
import * as yup from "yup";
import { Link as LinkRouter } from 'react-router-dom';
import YupPassword from 'yup-password';
import axios from './../../api/axios';
import { useFormik } from 'formik';
import { Box, Button, Container, TextField, Typography } from '@mui/material';
import { Nav, NavContainer } from '../Navbar/NavbarElements'
import { Icon } from './../SignIn/SigninElements'
import Alert from '@material-ui/lab/Alert';
YupPassword(yup)


// URL for user requests
const userUrl = '/user';


/**
 * 
 * @returns signUp Page
 */
const SignUp = () => {

    //for error handling
    const [iserror, setIserror] = useState(false)
    const [errorMessages, setErrorMessages] = useState([])

    const formik = useFormik({
        initialValues: {
            firstName: '',
            lastName: '',
            userName: '',
            password: '',
            confirmPassword: ''
        },
        validateOnChange: false,
        validate: (value) => {
            return (
                axios.get('/user?username=' + value.userName)
                    .then((response) => {
                        if (response) {
                            setIserror(true)
                            setErrorMessages(["Username alrady exisits"])
                            console.log(errorMessages)
                        } else {
                            setIserror(false)
                            setErrorMessages([])
                        }
                    }))
                    .catch((error) => {
                        setIserror(false)
                        setErrorMessages([])
                    })
        },
        validationSchema: yup.object({
            firstName: yup.string().required().max(255),
            lastName: yup.string().required().max(255),
            userName: yup.string().required().max(255),
            password: yup.string().password().required().max(255),
            confirmPassword: yup.string().oneOf([yup.ref('password'), null], "Passwords must match")
        }),
        // function for submission event handling
        // initializes api requests
        onSubmit: values => {

            alert(JSON.stringify({
                'pk': 1,
                'firstName': values.firstName,
                'lastName': values.lastName,
                'password': values.password,
                'username': values.userName
            }, null, 2));

            // post request to register new user
            axios
                .post(userUrl, JSON.stringify({
                    'pk': 1,
                    'username': values.userName,
                    'firstName': values.firstName,
                    'lastName': values.lastName,
                    'password': values.password
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
                                                    Create a new user
                                                </Typography>
                                                <Typography
                                                    color="textSecondary"
                                                    gutterBottom
                                                    variant="body2"
                                                >
                                                    Fill the information to create a new user
                                                </Typography>
                                            </Box>
                                            <div>
                                                {iserror &&
                                                    <Alert severity="error">
                                                        {errorMessages.map((msg, i) => {
                                                            return <div key={i}>{msg}</div>
                                                        })}
                                                    </Alert>
                                                }
                                            </div>
                                            <TextField
                                                error={Boolean(formik.touched.firstName && formik.errors.firstName)}
                                                fullWidth
                                                helperText={formik.touched.firstName && formik.errors.firstName}
                                                label="First Name"
                                                margin="normal"
                                                name="firstName"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                value={formik.values.firstName}
                                                variant="outlined"
                                            />
                                            <TextField
                                                error={Boolean(formik.touched.lastName && formik.errors.lastName)}
                                                fullWidth
                                                helperText={formik.touched.lastName && formik.errors.lastName}
                                                label="Last Name"
                                                margin="normal"
                                                name="lastName"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                value={formik.values.lastName}
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
                                            <TextField
                                                error={Boolean(formik.touched.confirmPassword && formik.errors.confirmPassword)}
                                                fullWidth
                                                helperText={formik.touched.confirmPassword && formik.errors.confirmPassword}
                                                label="Confirm Password"
                                                margin="normal"
                                                name="confirmPassword"
                                                onBlur={formik.handleBlur}
                                                onChange={formik.handleChange}
                                                type="password"
                                                value={formik.values.confirmPassword}
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
                                                    Sign Up Now
                                                </Button>
                                            </Box>
                                            <Typography
                                                color="textSecondary"
                                                variant="body2"
                                            >
                                                Have an account?
                                                {' '}

                                                <LinkRouter to="/signIn" id="RouterNavLink" style={{ color: '#F56300' }}>
                                                    Sign In
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

export default SignUp

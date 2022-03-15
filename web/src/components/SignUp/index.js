import React from 'react';
import { Icon, FormContent, Form, FormInput, FormH1, FormLabel, FormButton, FormError, Text } from './../SignIn/SigninElements';
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements';
import { Nav, NavContainer } from '../Navbar/NavbarElements';
import { useForm } from "react-hook-form";
import * as yup from "yup";
import { yupResolver } from '@hookform/resolvers/yup'
import YupPassword from 'yup-password';
import { ButtonComponentRouter } from '../../ButtonElement';
import axios from './../../api/axios';
YupPassword(yup)

// schema for form validation
const schema = yup.object({
    firstName: yup.string().required().min(3),
    lastName: yup.string().required(),
    password: yup.string().password().required(),
    confirmPassword: yup.string().oneOf([yup.ref('password'), null], "Passwords must match")
});

// URL for user requests
const userUrl = '/user';


/**
 * 
 * @returns signUp Page
 */
const SignUp = () => {

    // form custom hook from react-form-hook
    const { register, handleSubmit, formState: { errors } } = useForm({
        resolver: yupResolver(schema)
    });


    // function for submission event handling
    // initializes api requests
    const onSubmit = data => {
        // post request to register new user
        axios
            .post(userUrl, JSON.stringify({
                'pk': 1,
                'firstName': data.firstName,
                'lastName': data.lastName,
                'keyHash': data.password,
                'typeID': 1
            }),
                { headers: { 'Content-Type': 'application/json', crossDomain: true } }
            )
            .then(response => { console.log(response.data) })
            .catch(error => { console.log(error.data) });
        // testing get request
            // axios
        //     .get(userUrl
        //     )
        //     .then(response => { console.log(response.data) })
        //     .catch(error => { console.log(error.data) });
    };


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

                                <FormContent>
                                    <Form onSubmit={handleSubmit(onSubmit)}>
                                        <FormH1>Sign up for a new account</FormH1>

                                        <FormLabel htmlFor='firstName'>
                                            First Name<br />
                                            <FormError> {errors.firstName?.message} </FormError>
                                        </FormLabel>
                                        <FormInput {...register("firstName")} placeholder="Enter First Name" id="firstName" />

                                        <FormLabel htmlFor='lastName'>
                                            Last Name<br />
                                            <FormError> {errors.lastName?.message} </FormError>
                                        </FormLabel>
                                        <FormInput {...register("lastName")} placeholder="Enter Last Name" id="lastName" />


                                        <FormLabel htmlFor='password'>
                                            Password <br />
                                            <FormError> {errors.password?.message} </FormError>
                                        </FormLabel>
                                        <FormInput {...register("password")} placeholder="Enter Password" type="password" id="password" />

                                        <FormLabel htmlFor='confirmPassword'>
                                            Confirm Password <br />
                                            <FormError> {errors.confirmPassword?.message} </FormError>
                                        </FormLabel>
                                        <FormInput {...register("confirmPassword")} placeholder="Confirm Password" type="password" id="confirmPassword" />


                                        <FormButton type='submit'>Continue</FormButton>
                                        <Text>Already have an account?</Text>
                                        <ButtonComponentRouter to='/signin'>Sign In</ButtonComponentRouter>
                                    </Form>
                                </FormContent>
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

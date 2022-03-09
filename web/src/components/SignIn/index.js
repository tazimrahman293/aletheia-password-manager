import React from 'react'
import { Icon, FormContent, Form, FormInput, FormH1, FormLabel, FormButton, Text } from './SigninElements'
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, ImgWrap, Img } from './../DataSection/DataElements'
import { Nav, NavContainer } from '../Navbar/NavbarElements'

const SignIn = () => {
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
                                    <Form action='#'>
                                        <FormH1>Sign in to your account</FormH1>
                                        <FormLabel htmlFor='for'>User Name</FormLabel>
                                        <FormInput htmlFor='email' required />
                                        <FormLabel htmlFor='for'>Password</FormLabel>
                                        <FormInput htmlFor='password' required />
                                        <FormButton type='submit'>Continue</FormButton>
                                        <Text>Forgot password</Text>
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

export default SignIn

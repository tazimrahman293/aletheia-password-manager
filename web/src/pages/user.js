import React, { useState } from 'react'
import { Box, Container, Grid, Typography } from '@mui/material';
import { UserProfileDetails } from '../components/User/UserProfileDetails'
import NavbarUser from '../components/NavbarUser'
import SidebarUser from '../components/SidebarUser'
import ScrollToTop from '../components/ScrollToTop'
import { Column1, Column2, DataContainer, DataRow, DataWrapper, TextWrapper, ImgWrap, Img } from '../components/DataSection/DataElements';
import { Helmet } from "react-helmet";

const User = () => {

    const [isOpen, setIsOpen] = useState(false)

    const toggle = () => {
        setIsOpen(!isOpen)
    }

    //TODO: Convert this into formik object
    //TODO: Create API request of type PATCH to update user details
    return (
        <>
            <Helmet>
                <meta charSet="utf-8" />
                <title>User | Details</title>
            </Helmet>
            <SidebarUser isOpen={isOpen} toggle={toggle} />
            <ScrollToTop />
            <NavbarUser toggle={toggle} />
            <DataContainer lightBg='true' id='form'>
                <DataWrapper>
                    <DataRow imgStart='true'>
                        <Column1>
                            <TextWrapper>
                                <Box
                                    component="main"
                                    sx={{
                                        flexGrow: 1,
                                        py: 8
                                    }}
                                >
                                    <Container maxWidth="lg">
                                        <Typography
                                            color="#F56300"
                                            sx={{ mb: 3 }}
                                            variant="h4"
                                        >
                                            Account
                                        </Typography>
                                        <Grid
                                            item
                                            lg={8}
                                            md={6}
                                            xs={12}
                                        >
                                            <UserProfileDetails/>
                                        </Grid>
                                    </Container>
                                </Box>
                            </TextWrapper>
                        </Column1>
                        <Column2>
                            <ImgWrap>
                                <Img src={require('./../images/svg5.svg').default} alt='logo' />
                            </ImgWrap>
                        </Column2>
                    </DataRow>
                </DataWrapper>
            </DataContainer>
        </>
    )
};

export default User;
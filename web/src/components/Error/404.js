import { Box, Container, Typography } from '@mui/material';
import { ButtonComponentRouter } from '../../ButtonElement';

const NotFound = () => (
    <>
            <Container maxWidth="md" >
                <Box
                    sx={{
                        alignItems: 'center',
                        display: 'flex',
                        flexDirection: 'column'
                    }}
                    style={{marginTop: '10vh'}}

                >
                    <Typography
                        align="center"
                        color="textPrimary"
                        variant="h1"
                    >
                       404: The page you are looking for isn’t here
                    </Typography>
                    <Box sx={{ textAlign: 'center' }}>
                        <img
                            src={require('../../images/404_error.svg').default} alt='404'
                            style={{
                                marginTop: 50,
                                display: 'inline-block',
                                maxWidth: '100%',
                                width: 560
                            }}
                        />
                    </Box>
                    <ButtonComponentRouter to='/' smooth={true} duration={500} spy={true} exact='true' offset={-80} >
                        Go Back To Home
                    </ButtonComponentRouter>
                </Box>
            </Container>
    </>
);

export default NotFound;
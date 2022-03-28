import { Box, Container, Typography } from '@mui/material';
import { ButtonComponentRouter } from '../../ButtonElement';

const ServerDown = () => (
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
                       500: Server Down
                    </Typography>
                    <Box sx={{ textAlign: 'center' }}>
                        <img
                            src={require('../../images/server_down.svg').default} alt='404'
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

export default ServerDown;
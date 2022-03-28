import { Box, Button, Card, CardContent, CardHeader, Divider, Grid, TextField } from '@mui/material';
import { useFormik } from 'formik';
import axios from 'axios';

const userUpdateUrl = '/user'

export const UserProfileDetails = (props) => {

    const formik = useFormik({
        initialValues: {
            //TODO: Add initial values from the logged in users details
            firstName: '',
            lastName: '',
            userName: ''
        },
        validateOnChange: false,
        onSubmit: values => {

            axios
                .patch(userUpdateUrl , JSON.stringify({
                    firstName: values.firstName,
                    lastName: values.lastName,
                    userName: values.userName
                }),
                    { headers: { 'Content-Type': 'application/json', crossDomain: true } }
                )
                .then(response => {alert(JSON.stringify(response.data))})

                .catch(error => {console.log(error.data)})
        }
        
    })

    return (
        <form onSubmit={formik.handleSubmit}>
            <Card 
            variant="outlined"
            
            >
                <CardHeader
                    subheader="The information can be edited"
                    title="Profile"
                />
                <Divider />
                <CardContent>
                    <Grid
                        container
                        direction="column"
                        spacing={5}
                    >
                        <Grid
                            item
                            md={6}
                            xs={12}
                        >
                            <TextField
                                fullWidth
                                // helperText="Please specify the first name"
                                label="First name"
                                name="firstName"
                                onBlur={formik.handleBlur}
                                onChange={formik.handleChange}
                                required
                                value={formik.values.firstName}
                                variant="outlined"
                            />
                        </Grid>
                        <Grid
                            item
                            md={6}
                            xs={12}
                        >
                            <TextField
                                fullWidth
                                label="Last name"
                                name="lastName"
                                onBlur={formik.handleBlur}
                                onChange={formik.handleChange}
                                required
                                value={formik.values.lastName}
                                variant="outlined"
                            />
                        </Grid>
                        <Grid
                            item
                            md={12}
                            xs={12}
                        >
                        <TextField
                            fullWidth
                            label="User Name"
                            name="userName"
                            onBlur={formik.handleBlur}
                            onChange={formik.handleChange}
                            required
                            value={formik.values.userName}
                            variant="outlined"
                        />
                        </Grid>
                    </Grid>
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
                        Update Details
                    </Button>
                </Box>
            </Card>
        </form>
    );
};
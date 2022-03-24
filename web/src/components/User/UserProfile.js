import { Box, Button, Card, CardActions, CardContent, Divider, Typography } from '@mui/material';

const user = {
    name: 'Akash Gill'
};

export const UserProfile = (props) => (
    <Card {...props}>
        <CardContent>
            <Box
                sx={{
                    alignItems: 'center',
                    display: 'flex',
                    flexDirection: 'column'
                }}
            >
                <Typography
                    color="textPrimary"
                    gutterBottom
                    variant="h5"
                >
                    {user.name}
                </Typography>
                </Box>
        </CardContent>
        <Divider />
        <CardActions>
            <Button
                color="primary"
                fullWidth
                variant="text"
            >
                Upload picture
            </Button>
        </CardActions>
    </Card>
);
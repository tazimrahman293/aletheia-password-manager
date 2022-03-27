/**
 * CSS for SignIn component
 */
import styled from 'styled-components';
import { Link as LinkRouter} from 'react-router-dom';

export const Icon = styled(LinkRouter)`
  color: #F56300;
    justify-self: flex-start;
    cursor: pointer;
    font-size: 2rem;
    display: flex;
    align-items: center;
    margin-left: 24px;
    font-weight: bold;
    text-decoration: none;
`
export const FormContent = styled.div`
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;

  @media screen and (max-width: 480px) {
    padding: 10px;
  }
`
export const Form = styled.form`
  background-color: #f9f9f9;
  max-width: 400px;
  height: auto;
  width: 100%;
  z-index: 1;
  display: grid;
  margin: 0 auto;
  padding: 80px 32px;
  border-radius:4px;
  box-shadow: 0 1px 3px rgba( 0, 0, 0, 0.9);
  
  @media screen and (max-width: 480px) {
    padding: 32px 32px;
  }
  `
export const FormH1 = styled.h1`
  margin-bottom: 40px;
  color: #F56300;
  font-size: 20px;
  font-weight: 700;
  text-align: center;
`
export const FormError = styled.p`
  color: black;
  font-size: 15px;
`;

export const FormLabel = styled.label`
  margin-bottom: 8px;
  font-size: 20px;
  color: #F56300;
`
export const FormInput = styled.input`
  padding: 16px 16px;
  margin-bottom: 32px;
  border-radius: 4px;
`
export const FormButton = styled.button`
  background: #F56300;
  padding: 16px 0;
  border: none;
  border-radius: 4px;
  color: #fff;
  font-size: 20px;
  font-weight: 700;
  cursor: pointer;
`
export const Text = styled.span`
text-align: center;
margin-top: 24px;
color: #F56300;
font-size: 14px;
`

import styled from 'styled-components'
import {NavLink as LinkRouter} from 'react-router-dom'

export const NavLinkR = styled(LinkRouter)`
    color: black;    
    display: flex;
    align-items: center;
    text-decoration: none;
    font-size: 1.6rem;
    padding: 0 1rem;
    height: 100%;
    cursor: pointer;
    &.active {
        border-bottom: 3px solid #F56300;
    } 
    
`;
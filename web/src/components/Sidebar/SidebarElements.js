/**
 * CSS for Sidebar
 */
import styled from 'styled-components';
import {Link as LinkRouter} from 'react-router-dom';
import {Link as LinkScroll} from 'react-scroll'
import {FaTimes} from 'react-icons/fa'


export const SidebarContainer = styled.aside`
    position: fixed;
    z-index: 999;
    height: 100%;
    width: 100%;
    background: #0d0d0d;
    display: grid;
    top: 0;
    left: 0;
    transition: 0.3s ease-in-out;
    opacity: ${({isOpen}) => (isOpen ? '100%' : '0')};
    top : ${({isOpen}) => (isOpen ? '0' : '-100%')};
   
`;

export const CrossIcon = styled(FaTimes)`
    /* color:#02D48E; */
    color: #F56300;
`;

export const Icon = styled.div`
    position: absolute;
    top: 1.2rem;
    right: 1.5rem;
    background: transparent;
    font-size: 2rem;
    cursor: pointer;
    outline: none;
`;


export const SideBarWrapper = styled.div`
    color: #ffffff;
`;

export const SidebarMenu = styled.ul`
    position: relative;
    display: grid;
    grid-template-columns: 1fr;
    margin-top: 16rem;
    grid-template-rows: repeat(5, 100px);
    text-align: center;

    @media screen and (max-width: 480px){
        grid-template-rows: repeat(6, 60px);
    }
`;

export const SidebarLink = styled(LinkScroll)`
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 1.9rem;
    text-decoration: none;
    list-style: none;
    transition: 0.2s ease-in-out;
    color: #ffffff;
    cursor: pointer;

    &:hover {
        /* color: #02D48E; */
        color: #F56300;
        transition: 0.2s ease-in-out;
    }

`;

export const SidebarLinkRouter = styled(LinkRouter)`
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 1.9rem;
    text-decoration: none;
    list-style: none;
    transition: 0.2s ease-in-out;
    color: #ffffff;
    cursor: pointer;

    &:hover {
        /* color: #02D48E; */
        color: #F56300;
        transition: 0.2s ease-in-out;
    }

`;

export const SidebarButton = styled.div`
    display: flex;
    justify-content: center;
`;

export const SidebarButtonRouter = styled(LinkRouter)`
    border-radius: 50px;
    /* background: #01bf71; */
    background: #F56300;
    white-space: nowrap;
    padding: 16px 64px;
    color: #010606;
    font-size: 2rem;
    outline: none;
    border: none;
    cursor: pointer;
    transition: all 0.2s ease-in-out;
    text-decoration: none;

    &:hover {
        transition: all 0.2s ease-in-out;
        background: #fff;
        /* color: #010606; */
        color: #F56300;
    }


`;
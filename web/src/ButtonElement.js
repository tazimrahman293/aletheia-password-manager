import styled from "styled-components";
import { Link as LinkScroll } from "react-scroll";
import { Link as LinkRouter } from "react-router-dom";

/**
 * Reusable Button component
 */
export const ButtonComponent = styled(LinkScroll)`
    border-radius: 50px;
    /* background: ${({primary}) => (primary ? '#01bF71' : '#010606')}; */
    background: ${({primary}) => (primary ? '#fff' : '#F56300')};
    white-space: nowrap;
    padding: ${({big}) => (big ? '14px 48px' : '12px 30px')};
    color: ${({dark}) => (dark ? '#010606' : '#fff')};
    font-size: ${({fontbig}) => (fontbig ? '20px' : '16px')};
    outline: none;
    border: none;
    cursor: pointer;
    display: flex;
    justify-content: center;
    align-items: center;
    transition: all 0.2s ease-in-out;
    z-index: 10;

    &:hover {
        transition: all 0.2s ease-in-out;
        background: ${({primary}) => (primary ? '#F56300': '#fff')};
        color: #F56300;
;

        
    }
`;

export const ButtonComponentRouter = styled(LinkRouter)`
    border-radius: 50px;
    /* background: ${({primary}) => (primary ? '#01bF71' : '#010606')}; */
    background: ${({primary}) => (primary ? '#fff' : '#F56300')};
    white-space: nowrap;
    padding: ${({big}) => (big ? '14px 48px' : '12px 30px')};
    color: ${({dark}) => (dark ? '#010606' : '#fff')};
    font-size: ${({fontBig}) => (fontBig ? '20px' : '16px')};
    outline: none;
    border: none;
    cursor: pointer;
    display: flex;
    justify-content: center;
    align-items: center;
    transition: all 0.2s ease-in-out;
    z-index: 10;

    &:hover {
        transition: all 0.2s ease-in-out;
        background: ${({primary}) => (primary ? '#F56300': '#fff')};
        color: #F56300;
;

        
    }
`;
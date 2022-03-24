/**
 * This file contains JSON objects used to build DataSection pages
 */
export const dataAbout = {
    id: 'about',
    to: '/signUp',
    lightBg: true,
    lightText: false,
    lighttextDesc: false,
    topLine: 'Safety First',
    headline: 'Store unlimited passwords with convinience',
    description: 'Aletheia is a password manager which provides users with a secure method for storing and managing passwords.',
    buttonLabel: 'Get started',
    imgStart: false,
    img: require('../../images/svg5.svg').default,
    alt: 'svg5',
    dark: false,
    primary: false,
    darkText: true
  };

  export const dataFeautures = {
    id: 'features',
    to: '/signUp',
    lightBg: false,
    lightText: true,
    lighttextDesc: false,
    topLine: 'Features',
    headline: 'Heading',
    description: 'Description',
    buttonLabel: 'Get started',
    imgStart: true,
    img: require('../../images/svg4.svg').default,
    alt: 'svg4',
    dark: false,
    primary: false,
    darkText: false
  };
import React from 'react'
import Icon1 from '../../images/svg1.svg'
import Icon2 from '../../images/svg2.svg'
import Icon3 from '../../images/svg3.svg'
import {FeaturesContainer, FeaturesH1, FeaturesWrapper, FeaturesCard, FeaturesIcon, FeaturesH2, FeaturesP} from './FeaturesElements'

const Features = () => {
  return (
    <FeaturesContainer id='features'>
      <FeaturesH1>Our services</FeaturesH1>
      <FeaturesWrapper>
        <FeaturesCard>
          <FeaturesIcon src={Icon1}/>
          <FeaturesH2>Heading</FeaturesH2>
          <FeaturesP>Description</FeaturesP>
        </FeaturesCard>
        <FeaturesCard>
        <FeaturesIcon src={Icon2}/>
        <FeaturesH2>Heading</FeaturesH2>
          <FeaturesP>Description</FeaturesP>
        </FeaturesCard>
        <FeaturesCard>
          <FeaturesIcon src={Icon3}/>
          <FeaturesH2>Heading</FeaturesH2>
          <FeaturesP>Description</FeaturesP>
        </FeaturesCard>
        <FeaturesCard>
          <FeaturesIcon src={Icon3}/>
          <FeaturesH2>Heading</FeaturesH2>
          <FeaturesP>Description</FeaturesP>
        </FeaturesCard>
      </FeaturesWrapper>
    </FeaturesContainer>
  )
}

export default Features

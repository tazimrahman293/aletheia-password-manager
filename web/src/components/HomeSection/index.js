import React, {useState} from 'react'
import Video from '../../videos/bg2.mp4'
import { HomeContainer, HomeBg, VideoBg, HomeContent, HomeH1, HomeP, HomeBtnWrapper, ArrowForward, ArrowRight } from './HomeElements'
import { ButtonComponent } from '../../ButtonElement'

/**
 * 
 * @returns HomeSection page
 */
const HomeSection = () => {
  const [hover, setHover] = useState(false);

  const onHover = () => {
    setHover(!hover)
  }

  return (
    <HomeContainer id='home'>
      <HomeBg>
        <VideoBg autoPlay loop muted src={Video} type='video/mp4' />
      </HomeBg>
      <HomeContent>
        <HomeH1> Security is not just a feature. It’s our foundation.</HomeH1>
        <HomeP>Every design decision in Aletheia begins with the safety and privacy of your data in mind.</HomeP>
        <HomeBtnWrapper>
          <ButtonComponent to='about' onMouseEnter={onHover} onMouseLeave={onHover}  big="true" fontbig="true"  smooth="true" duration={500} spy={true} exact="true" offset={-80}>
            Learn More {hover ? <ArrowForward /> : <ArrowRight/>}
          </ButtonComponent>
        </HomeBtnWrapper>
      </HomeContent>
    </HomeContainer>
  )
}

export default HomeSection

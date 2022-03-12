import React from 'react'
import Icon1 from '../../images/svg1.svg'
import Icon2 from '../../images/svg2.svg'
import Icon3 from '../../images/svg3.svg'
import {TeamContainer, TeamH1, TeamWrapper, TeamCard, TeamIcon, TeamH2, TeamP} from './TeamElements'

/**
 * 
 * @returns Team page
 */
const Team = () => {
  return (
    <TeamContainer id='team'>
      <TeamH1>Meet The Team</TeamH1>
      <TeamWrapper>
        <TeamCard>
          <TeamIcon src={Icon1}/>
          <TeamH2>Jeremy</TeamH2>
          <TeamP>Description</TeamP>
        </TeamCard>
        <TeamCard>
        <TeamIcon src={Icon2}/>
        <TeamH2>Tyrel</TeamH2>
          <TeamP>Description</TeamP>
        </TeamCard>
        <TeamCard>
          <TeamIcon src={Icon3}/>
          <TeamH2>Tazim</TeamH2>
          <TeamP>Description</TeamP>
        </TeamCard>
        <TeamCard>
          <TeamIcon src={Icon3}/>
          <TeamH2>Akash</TeamH2>
          <TeamP>Description</TeamP>
        </TeamCard>
      </TeamWrapper>
    </TeamContainer>
  )
}

export default Team

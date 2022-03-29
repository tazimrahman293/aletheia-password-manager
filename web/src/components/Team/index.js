import React from 'react'
import Icon1 from '../../images/wallet.svg'
import Icon2 from '../../images/svg2.svg'
import Icon3 from '../../images/productivity.svg'
import Icon4 from '../../images/personal.svg'
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
          <TeamP>Senior Year Computer Engineering</TeamP>
        </TeamCard>
        <TeamCard>
        <TeamIcon src={Icon2}/>
        <TeamH2>Tyrel</TeamH2>
          <TeamP>Senior Year Computer Engineering</TeamP>
        </TeamCard>
        <TeamCard>
          <TeamIcon src={Icon4}/>
          <TeamH2>Tazim</TeamH2>
          <TeamP>3rd-Year Computer Engineering</TeamP>
        </TeamCard>
        <TeamCard>
          <TeamIcon src={Icon3}/>
          <TeamH2>Akash</TeamH2>
          <TeamP>3rd-Year Computer Science</TeamP>
        </TeamCard>
      </TeamWrapper>
    </TeamContainer>
  )
}

export default Team

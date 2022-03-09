import React from 'react'
import { ButtonComponent } from '../../ButtonElement'
// import { ssvg1.svg } from '../../images/svg1.svg'
import { DataContainer, DataWrapper, DataRow, Column1, Column2, TextWrapper, TopLine, Heading, Subtitle, BtnWrap, ImgWrap, Img } from './DataElements'

const DataSection = ({ lightBg, id, imgStart, topLine, lightText, headline, darkText, description, buttonLabel, alt, img, primary, dark, dark2 }) => {
    return (
        <>
            <DataContainer lightBg={lightBg} id={id}>
                <DataWrapper>
                    <DataRow imgStart={imgStart}>
                        <Column1>
                            <TextWrapper>
                                <TopLine>{topLine}</TopLine>
                                <Heading lightText={lightText}>{headline}</Heading>
                                <Subtitle darkText={darkText}>{description}</Subtitle>
                                <BtnWrap>
                                    <ButtonComponent to='home' smooth={true} duration={500} spy={true} exact='true' offset={-80} primary={primary ? 1 : 0} dark={dark ? 1 : 0} dark2={dark2 ? 1 : 0}>
                                        {buttonLabel}
                                    </ButtonComponent>
                                </BtnWrap>
                            </TextWrapper>
                        </Column1>
                        <Column2>
                            <ImgWrap>
                                <Img src={img} alt={alt} />
                            </ImgWrap>
                        </Column2>
                    </DataRow>
                </DataWrapper>
            </DataContainer>
        </>
    )
}

export default DataSection
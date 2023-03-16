/**
 * @file
 * @author Miguel Mejía Jiménez
 * @copyright MIT License
 * @brief This file contains the RadialLight class.
 */
#ifndef __CANDLE_RADIAL_LIGHT_HPP__
#define __CANDLE_RADIAL_LIGHT_HPP__

#define RADIAL_LIGHT_FIX
//#define CANDLE_DEBUG

#include "Candle/LightSource.hpp"
#include "Candle/graphics/VertexArray.hpp"

namespace candle{
    /**
     * @brief LightSource that emits light from a single point
     * @details
     *
     * A RadialLight is defined, mainly, by the position, the orientation, the
	 * range of the light and the beam angle. To manipulate the
     * position and the orientation of the light, you can change the position
	 * and rotation of the object as you would do with any sf::Transformable.
	 * The range can be manipulated as with other LightSources, with
     * @ref LightSource::setRange, and the angle of the beam with
	 * @ref setBeamAngle.
     *
     * <table width="100%">
     * <tr>
     *  <td align="center"> <img src="radial_1.png" width="300px"> <br> <em>Variables schema</em> </td>
     *  <td align="center"> <img src="radial_2.png" width="300px"> <br> <em>Demo example</em> </td>
     * </tr>
     * </table>
     */
    class RadialLight: public LightSource{
    private:
        static int s_instanceCount;
        const float BASE_RADIUS = 400.0f;
        float m_beamAngle;
        std::unique_ptr<sf::RenderTexture> l_lightTextureFade;
        std::unique_ptr<sf::RenderTexture> l_lightTexturePlain;

        void draw(sf::RenderTarget& t, sf::RenderStates st) const override;
        void resetColor() override;

        void initializeTextures() {
#ifdef CANDLE_DEBUG
            std::cout << "RadialLight: InitializeTextures" << std::endl;
#endif
            int points = 100;

            l_lightTextureFade.reset(new sf::RenderTexture);
            l_lightTexturePlain.reset(new sf::RenderTexture);
            l_lightTextureFade->create(BASE_RADIUS * 2 + 2, BASE_RADIUS * 2 + 2);
            l_lightTexturePlain->create(BASE_RADIUS * 2 + 2, BASE_RADIUS * 2 + 2);

            sf::VertexArray lightShape(sf::TriangleFan, points + 2);
            float step = sfu::PI * 2.f / points;
            lightShape[0].position = { BASE_RADIUS + 1, BASE_RADIUS + 1 };
            for (int i = 1; i < points + 2; i++) {
                lightShape[i].position = {
                    (std::sin(step * (i)) + 1) * BASE_RADIUS + 1,
                    (std::cos(step * (i)) + 1) * BASE_RADIUS + 1
                };
                lightShape[i].color.a = 0;
            }
            l_lightTextureFade->clear(sf::Color::Transparent);
            l_lightTextureFade->draw(lightShape);
            l_lightTextureFade->display();
            l_lightTextureFade->setSmooth(true);

            sfu::setColor(lightShape, sf::Color::White);
            l_lightTexturePlain->clear(sf::Color::Transparent);
            l_lightTexturePlain->draw(lightShape);
            l_lightTexturePlain->display();
            l_lightTexturePlain->setSmooth(true);
        }

    public:
        
        /**
         * @brief Constructor
         */
        RadialLight();

        /**
         * @brief Destructor
         */
        virtual ~RadialLight();

        void castLight(const EdgeVector::iterator& begin, const EdgeVector::iterator& end) override;

        /**
         * @brief Set the range for which rays may be casted.
         * @details The angle shall be specified in degrees. The angle in which the rays will be casted will be
         * [R - angle/2, R + angle/2], where R is the rotation of the object.
         * @param angle
         * @see getBeamAngle
         */
        void setBeamAngle(float angle);

        /**
         * @brief Get the range for which rays may be casted.
         * @details It defaults to 360º.
         * @see setBeamAngle
         */
        float getBeamAngle() const;

        /**
         * @brief Get the local bounding rectangle of the light.
         * @returns The local bounding rectangle in float.
         */
        sf::FloatRect getLocalBounds() const;

        /**
         * @brief Get the global bounding rectangle of the light.
         * @returns The global bounding rectangle in float.
         */
        sf::FloatRect getGlobalBounds() const;

    };
}

#endif

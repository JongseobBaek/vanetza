#ifndef SECURITY_ENTITY_HPP
#define SECURITY_ENTITY_HPP

#include <vanetza/common/clock.hpp>
#include <vanetza/security/decap_confirm.hpp>
#include <vanetza/security/decap_request.hpp>
#include <vanetza/security/encap_confirm.hpp>
#include <vanetza/security/encap_request.hpp>
#include <memory>

namespace vanetza
{
namespace security
{

// forward declarations
class Backend;
class CertificateManager;

class SecurityEntity
{
public:
    /**
     * \param time_now timestamp referring to current time
     */
    SecurityEntity(const Clock::time_point& time_now);

    /**
     * \brief Creates a security envelope covering the given payload.
     *
     * The payload consists of the CommonHeader, ExtendedHeader and the payload of
     * the layers above the network layer. The entire security envelope is used
     * to calculate a signature which gets added to the resulting SecuredMessage.
     *
     * \param request containing payload to sign
     * \return confirmation containing signed SecuredMessage
     */
    EncapConfirm encapsulate_packet(const EncapRequest& encap_request);

    /** \brief decapsulates packet
     *
     * \param packet that should be decapsulated
     * \return decapsulated packet
     */
    DecapConfirm decapsulate_packet(const DecapRequest& decap_request);

    /**
     * \brief enable deferred signature creation
     *
     * SecuredMessages contain EcdsaSignatureFuture instead of EcdsaSignature
     * when this feature is enabled.
     *
     * \param flag true for enabling deferred signature calculation
     */
    void enable_deferred_signing(bool flag);

private:
    /** \brief sign the packet
    *
    * \param encap request that was handed over
    * \return signed packet
    */
    EncapConfirm sign(const EncapRequest& encap_request);

    /** \brief verify the packet
    *
    * \param signed packet
    * \return verified packet
    */
    DecapConfirm verify(const DecapRequest& decap_request);

    const Clock::time_point& m_time_now;
    bool m_sign_deferred; /*< controls if EcdsaSignatureFuture is used */
    std::shared_ptr<CertificateManager> m_certificate_manager;
    std::shared_ptr<Backend> m_crypto_backend;
};

} // namespace security
} // namespace vanetza

#endif // SECURITY_ENTITY_HPP

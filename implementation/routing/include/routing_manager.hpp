// Copyright (C) 2014 BMW Group
// Author: Lutz Bichler (lutz.bichler@bmw.de)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef VSOMEIP_ROUTING_MANAGER
#define VSOMEIP_ROUTING_MANAGER

#include <memory>
#include <set>
#include <vector>

#include <boost/asio/io_service.hpp>

#include <vsomeip/message.hpp>

namespace vsomeip {

class endpoint;
class event;
class service_info;

class routing_manager {
public:
	virtual ~routing_manager() {};

	virtual boost::asio::io_service & get_io() = 0;

	virtual void init() = 0;
	virtual void start() = 0;
	virtual void stop() = 0;

	virtual void offer_service(client_t _client,
					service_t _service, instance_t _instance,
					major_version_t _major, minor_version_t _minor, ttl_t _ttl) = 0;

	virtual void stop_offer_service(client_t _client,
					service_t _service, instance_t _instance) = 0;

	virtual void publish_eventgroup(client_t _client,
					service_t _service, instance_t _instance,
			 	 	eventgroup_t _eventgroup,
					major_version_t _major, ttl_t _ttl) = 0;

	virtual void stop_publish_eventgroup(client_t _client,
					service_t _service, instance_t _instance,
					eventgroup_t _eventgroup) = 0;

	virtual std::shared_ptr< event > add_event(client_t _client,
					service_t _service, instance_t _instance,
					eventgroup_t _eventgroup, event_t _event) = 0;

	virtual std::shared_ptr< event > add_field(client_t _client,
					service_t _service, instance_t _instance,
					eventgroup_t _eventgroup, event_t _event,
					std::shared_ptr< payload > _payload) = 0;

	virtual void remove_event_or_field(std::shared_ptr< event > _event) = 0;

	virtual void request_service(client_t _client,
					service_t _service, instance_t _instance,
					major_version_t _major, minor_version_t _minor,	ttl_t _ttl) = 0;

	virtual void release_service(client_t _client,
					service_t _service, instance_t _instance) = 0;

	virtual void subscribe(client_t _client,
					service_t _service, instance_t _instance, eventgroup_t _eventgroup) = 0;

	virtual void unsubscribe(client_t _client,
					service_t _service, instance_t _instance, eventgroup_t _eventgroup) = 0;

	virtual void send(client_t _client,
			std::shared_ptr< message > _message, bool _flush, bool _reliable) = 0;

	virtual void send(client_t _client,
				const byte_t *_data, uint32_t _size, instance_t _instance, bool _flush, bool _reliable) = 0;

	virtual void set(client_t _client,
					service_t _service, instance_t _instance,
			      	event_t _event, const std::vector< byte_t > &_value) = 0;

	virtual bool is_available(service_t _service, instance_t _instance) const = 0;

	virtual endpoint * find_local(client_t _client) = 0;
	virtual endpoint * find_local(service_t _service, instance_t _instance) = 0;
	virtual endpoint * find_or_create_local(client_t _client) = 0;
	virtual void remove_local(client_t _client) = 0;
};

} // namespace vsomeip

#endif

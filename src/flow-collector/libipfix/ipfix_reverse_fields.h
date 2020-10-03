/* 
 * IPFIX structs, types and definitions
 *
 * This is a generated file. Do not edit! 
 *
 */

/* ipfix information element list
 */
ipfix_field_type_t ipfix_reverse_field_types[] = {
   { REV_PEN, IPFIX_FT_OCTETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse octetDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_PACKETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse packetDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse flows", (char*)"reverse Netflow Number of Flows that were aggregated" },
   { REV_PEN, IPFIX_FT_PROTOCOLIDENTIFIER, 1, IPFIX_CODING_UINT, 
     (char*)"reverse protocolIdentifier", (char*)"" },
   { REV_PEN, IPFIX_FT_IPCLASSOFSERVICE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipClassOfService", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPCONTROLBITS, 1, IPFIX_CODING_UINT, 
     (char*)"reverse tcpControlBits", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCETRANSPORTPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse sourceTransportPort", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse sourceIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV4PREFIXLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse sourceIPv4PrefixLength", (char*)"" },
   { REV_PEN, IPFIX_FT_INGRESSINTERFACE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse ingressInterface", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONTRANSPORTPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse destinationTransportPort", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse destinationIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV4PREFIXLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse destinationIPv4PrefixLength", (char*)"" },
   { REV_PEN, IPFIX_FT_EGRESSINTERFACE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse egressInterface", (char*)"" },
   { REV_PEN, IPFIX_FT_IPNEXTHOPIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse ipNextHopIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPSOURCEASNUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse bgpSourceAsNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPDESTINATIONASNUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse bgpDestinationAsNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPNEXTHOPIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse bgpNextHopIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTMCASTPACKETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postMCastPacketDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTMCASTOCTETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postMCastOctetDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDSYSUPTIME, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowEndSysUpTime", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTSYSUPTIME, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowStartSysUpTime", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTOCTETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postOctetDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTPACKETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postPacketDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_MINIMUMIPTOTALLENGTH, 8, IPFIX_CODING_UINT, 
     (char*)"reverse minimumIpTotalLength", (char*)"" },
   { REV_PEN, IPFIX_FT_MAXIMUMIPTOTALLENGTH, 8, IPFIX_CODING_UINT, 
     (char*)"reverse maximumIpTotalLength", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse sourceIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse destinationIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV6PREFIXLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse sourceIPv6PrefixLength", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV6PREFIXLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse destinationIPv6PrefixLength", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWLABELIPV6, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowLabelIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPTYPECODEIPV4, 2, IPFIX_CODING_UINT, 
     (char*)"reverse icmpTypeCodeIPv4", (char*)"" },
   { REV_PEN, IPFIX_FT_IGMPTYPE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse igmpType", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLING_INTERVAL, 4, IPFIX_CODING_UINT, 
     (char*)"reverse sampling_interval", (char*)"reverse Netflow Sampling Interval" },
   { REV_PEN, IPFIX_FT_SAMPLING_ALGORITHM, 1, IPFIX_CODING_UINT, 
     (char*)"reverse sampling_algorithm", (char*)"reverse Netflow Sampling Algorithm" },
   { REV_PEN, IPFIX_FT_FLOWACTIVETIMEOUT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse flowActiveTimeout", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWIDLETIMEOUT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse flowIdleTimeout", (char*)"" },
   { REV_PEN, IPFIX_FT_ENGINE_TYPE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse engine_type", (char*)"reverse Netflow Engine Type" },
   { REV_PEN, IPFIX_FT_ENGINE_ID, 1, IPFIX_CODING_UINT, 
     (char*)"reverse engine_id", (char*)"reverse Netflow Engine ID" },
   { REV_PEN, IPFIX_FT_EXPORTEDOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse exportedOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTEDMESSAGETOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse exportedMessageTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTEDFLOWRECORDTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse exportedFlowRecordTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV4PREFIX, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse sourceIPv4Prefix", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV4PREFIX, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse destinationIPv4Prefix", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELTYPE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse mplsTopLabelType", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse mplsTopLabelIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOW_SAMPLER_ID, 1, IPFIX_CODING_UINT, 
     (char*)"reverse flow_sampler_id", (char*)"reverse Netflow Flow Sampler ID" },
   { REV_PEN, IPFIX_FT_FLOW_SAMPLER_MODE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse flow_sampler_mode", (char*)"reverse Netflow Flow Sampler Mode" },
   { REV_PEN, IPFIX_FT_FLOW_SAMPLER_RANDOM_INTERVAL, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flow_sampler_random_interval", (char*)"reverse Netflow Packet Sample Interval" },
   { REV_PEN, IPFIX_FT_MINIMUMTTL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse minimumTTL", (char*)"" },
   { REV_PEN, IPFIX_FT_MAXIMUMTTL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse maximumTTL", (char*)"" },
   { REV_PEN, IPFIX_FT_FRAGMENTIDENTIFICATION, 4, IPFIX_CODING_UINT, 
     (char*)"reverse fragmentIdentification", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTIPCLASSOFSERVICE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse postIpClassOfService", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEMACADDRESS, 6, IPFIX_CODING_BYTES, 
     (char*)"reverse sourceMacAddress", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTDESTINATIONMACADDRESS, 6, IPFIX_CODING_BYTES, 
     (char*)"reverse postDestinationMacAddress", (char*)"" },
   { REV_PEN, IPFIX_FT_VLANID, 2, IPFIX_CODING_UINT, 
     (char*)"reverse vlanId", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTVLANID, 2, IPFIX_CODING_UINT, 
     (char*)"reverse postVlanId", (char*)"" },
   { REV_PEN, IPFIX_FT_IPVERSION, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipVersion", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWDIRECTION, 1, IPFIX_CODING_UINT, 
     (char*)"reverse flowDirection", (char*)"" },
   { REV_PEN, IPFIX_FT_IPNEXTHOPIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse ipNextHopIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPNEXTHOPIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse bgpNextHopIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_IPV6EXTENSIONHEADERS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse ipv6ExtensionHeaders", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELSTACKSECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsTopLabelStackSection", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION2, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection2", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION3, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection3", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION4, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection4", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION5, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection5", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION6, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection6", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION7, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection7", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION8, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection8", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION9, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection9", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION10, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection10", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONMACADDRESS, 6, IPFIX_CODING_BYTES, 
     (char*)"reverse destinationMacAddress", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTSOURCEMACADDRESS, 6, IPFIX_CODING_BYTES, 
     (char*)"reverse postSourceMacAddress", (char*)"" },
   { REV_PEN, IPFIX_FT_OCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse octetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_PACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse packetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_FRAGMENTOFFSET, 2, IPFIX_CODING_UINT, 
     (char*)"reverse fragmentOffset", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSVPNROUTEDISTINGUISHER, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsVpnRouteDistinguisher", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPNEXTADJACENTASNUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse bgpNextAdjacentAsNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_BGPPREVADJACENTASNUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse bgpPrevAdjacentAsNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTERIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse exporterIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTERIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse exporterIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_DROPPEDOCTETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse droppedOctetDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_DROPPEDPACKETDELTACOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse droppedPacketDeltaCount", (char*)"" },
   { REV_PEN, IPFIX_FT_DROPPEDOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse droppedOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_DROPPEDPACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse droppedPacketTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDREASON, 1, IPFIX_CODING_UINT, 
     (char*)"reverse flowEndReason", (char*)"" },
   { REV_PEN, IPFIX_FT_COMMONPROPERTIESID, 8, IPFIX_CODING_UINT, 
     (char*)"reverse commonPropertiesId", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONPOINTID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse observationPointId", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPTYPECODEIPV6, 2, IPFIX_CODING_UINT, 
     (char*)"reverse icmpTypeCodeIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse mplsTopLabelIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_LINECARDID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse lineCardId", (char*)"" },
   { REV_PEN, IPFIX_FT_PORTID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse portId", (char*)"" },
   { REV_PEN, IPFIX_FT_METERINGPROCESSID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse meteringProcessId", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTINGPROCESSID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse exportingProcessId", (char*)"" },
   { REV_PEN, IPFIX_FT_TEMPLATEID, 2, IPFIX_CODING_UINT, 
     (char*)"reverse templateId", (char*)"" },
   { REV_PEN, IPFIX_FT_WLANCHANNELID, 1, IPFIX_CODING_UINT, 
     (char*)"reverse wlanChannelId", (char*)"" },
   { REV_PEN, IPFIX_FT_WLANSSID, 65535, IPFIX_CODING_STRING, 
     (char*)"reverse wlanSSID", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWID, 8, IPFIX_CODING_UINT, 
     (char*)"reverse flowId", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONDOMAINID, 4, IPFIX_CODING_UINT, 
     (char*)"reverse observationDomainId", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTSECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowStartSeconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDSECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowEndSeconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTMILLISECONDS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse flowStartMilliseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDMILLISECONDS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse flowEndMilliseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTMICROSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse flowStartMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDMICROSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse flowEndMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTNANOSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse flowStartNanoseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDNANOSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse flowEndNanoseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWSTARTDELTAMICROSECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowStartDeltaMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWENDDELTAMICROSECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowEndDeltaMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_SYSTEMINITTIMEMILLISECONDS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse systemInitTimeMilliseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWDURATIONMILLISECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowDurationMilliseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWDURATIONMICROSECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse flowDurationMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVEDFLOWTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse observedFlowTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_IGNOREDPACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse ignoredPacketTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_IGNOREDOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse ignoredOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_NOTSENTFLOWTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse notSentFlowTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_NOTSENTPACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse notSentPacketTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_NOTSENTOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse notSentOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_DESTINATIONIPV6PREFIX, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse destinationIPv6Prefix", (char*)"" },
   { REV_PEN, IPFIX_FT_SOURCEIPV6PREFIX, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse sourceIPv6Prefix", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTPACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postPacketTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_FLOWKEYINDICATOR, 8, IPFIX_CODING_UINT, 
     (char*)"reverse flowKeyIndicator", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTMCASTPACKETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postMCastPacketTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTMCASTOCTETTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse postMCastOctetTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPTYPEIPV4, 1, IPFIX_CODING_UINT, 
     (char*)"reverse icmpTypeIPv4", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPCODEIPV4, 1, IPFIX_CODING_UINT, 
     (char*)"reverse icmpCodeIPv4", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPTYPEIPV6, 1, IPFIX_CODING_UINT, 
     (char*)"reverse icmpTypeIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_ICMPCODEIPV6, 1, IPFIX_CODING_UINT, 
     (char*)"reverse icmpCodeIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_UDPSOURCEPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse udpSourcePort", (char*)"" },
   { REV_PEN, IPFIX_FT_UDPDESTINATIONPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse udpDestinationPort", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPSOURCEPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse tcpSourcePort", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPDESTINATIONPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse tcpDestinationPort", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPSEQUENCENUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse tcpSequenceNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPACKNOWLEDGEMENTNUMBER, 4, IPFIX_CODING_UINT, 
     (char*)"reverse tcpAcknowledgementNumber", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPWINDOWSIZE, 2, IPFIX_CODING_UINT, 
     (char*)"reverse tcpWindowSize", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPURGENTPOINTER, 2, IPFIX_CODING_UINT, 
     (char*)"reverse tcpUrgentPointer", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPHEADERLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse tcpHeaderLength", (char*)"" },
   { REV_PEN, IPFIX_FT_IPHEADERLENGTH, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipHeaderLength", (char*)"" },
   { REV_PEN, IPFIX_FT_TOTALLENGTHIPV4, 2, IPFIX_CODING_UINT, 
     (char*)"reverse totalLengthIPv4", (char*)"" },
   { REV_PEN, IPFIX_FT_PAYLOADLENGTHIPV6, 2, IPFIX_CODING_UINT, 
     (char*)"reverse payloadLengthIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_IPTTL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipTTL", (char*)"" },
   { REV_PEN, IPFIX_FT_NEXTHEADERIPV6, 1, IPFIX_CODING_UINT, 
     (char*)"reverse nextHeaderIPv6", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSPAYLOADLENGTH, 4, IPFIX_CODING_UINT, 
     (char*)"reverse mplsPayloadLength", (char*)"" },
   { REV_PEN, IPFIX_FT_IPDIFFSERVCODEPOINT, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipDiffServCodePoint", (char*)"" },
   { REV_PEN, IPFIX_FT_IPPRECEDENCE, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipPrecedence", (char*)"" },
   { REV_PEN, IPFIX_FT_FRAGMENTFLAGS, 1, IPFIX_CODING_UINT, 
     (char*)"reverse fragmentFlags", (char*)"" },
   { REV_PEN, IPFIX_FT_OCTETDELTASUMOFSQUARES, 8, IPFIX_CODING_UINT, 
     (char*)"reverse octetDeltaSumOfSquares", (char*)"" },
   { REV_PEN, IPFIX_FT_OCTETTOTALSUMOFSQUARES, 8, IPFIX_CODING_UINT, 
     (char*)"reverse octetTotalSumOfSquares", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELTTL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse mplsTopLabelTTL", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKLENGTH, 4, IPFIX_CODING_UINT, 
     (char*)"reverse mplsLabelStackLength", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKDEPTH, 4, IPFIX_CODING_UINT, 
     (char*)"reverse mplsLabelStackDepth", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSTOPLABELEXP, 1, IPFIX_CODING_UINT, 
     (char*)"reverse mplsTopLabelExp", (char*)"" },
   { REV_PEN, IPFIX_FT_IPPAYLOADLENGTH, 4, IPFIX_CODING_UINT, 
     (char*)"reverse ipPayloadLength", (char*)"" },
   { REV_PEN, IPFIX_FT_UDPMESSAGELENGTH, 2, IPFIX_CODING_UINT, 
     (char*)"reverse udpMessageLength", (char*)"" },
   { REV_PEN, IPFIX_FT_ISMULTICAST, 1, IPFIX_CODING_UINT, 
     (char*)"reverse isMulticast", (char*)"" },
   { REV_PEN, IPFIX_FT_IPV4IHL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse ipv4IHL", (char*)"" },
   { REV_PEN, IPFIX_FT_IPV4OPTIONS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse ipv4Options", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPOPTIONS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpOptions", (char*)"" },
   { REV_PEN, IPFIX_FT_PADDINGOCTETS, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse paddingOctets", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORIPV4ADDRESS, 4, IPFIX_CODING_IPADDR, 
     (char*)"reverse collectorIPv4Address", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORIPV6ADDRESS, 16, IPFIX_CODING_IPADDR, 
     (char*)"reverse collectorIPv6Address", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORINTERFACE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse collectorInterface", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORPROTOCOLVERSION, 1, IPFIX_CODING_UINT, 
     (char*)"reverse collectorProtocolVersion", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORTRANSPORTPROTOCOL, 1, IPFIX_CODING_UINT, 
     (char*)"reverse collectorTransportProtocol", (char*)"" },
   { REV_PEN, IPFIX_FT_COLLECTORTRANSPORTPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse collectorTransportPort", (char*)"" },
   { REV_PEN, IPFIX_FT_EXPORTERTRANSPORTPORT, 2, IPFIX_CODING_UINT, 
     (char*)"reverse exporterTransportPort", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPSYNTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpSynTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPFINTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpFinTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPRSTTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpRstTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPPSHTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpPshTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPACKTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpAckTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPURGTOTALCOUNT, 8, IPFIX_CODING_UINT, 
     (char*)"reverse tcpUrgTotalCount", (char*)"" },
   { REV_PEN, IPFIX_FT_IPTOTALLENGTH, 8, IPFIX_CODING_UINT, 
     (char*)"reverse ipTotalLength", (char*)"" },
   { REV_PEN, IPFIX_FT_POSTMPLSTOPLABELEXP, 1, IPFIX_CODING_UINT, 
     (char*)"reverse postMplsTopLabelExp", (char*)"" },
   { REV_PEN, IPFIX_FT_TCPWINDOWSCALE, 2, IPFIX_CODING_UINT, 
     (char*)"reverse tcpWindowScale", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONPOINTID_PSAMP, 8, IPFIX_CODING_UINT, 
     (char*)"reverse observationPointId_PSAMP", (char*)"" },
   { REV_PEN, IPFIX_FT_SELECTIONSEQUENCEID, 8, IPFIX_CODING_UINT, 
     (char*)"reverse selectionSequenceId", (char*)"" },
   { REV_PEN, IPFIX_FT_SELECTORID, 2, IPFIX_CODING_UINT, 
     (char*)"reverse selectorId", (char*)"" },
   { REV_PEN, IPFIX_FT_INFORMATIONELEMENTID, 2, IPFIX_CODING_UINT, 
     (char*)"reverse informationElementId", (char*)"" },
   { REV_PEN, IPFIX_FT_SELECTORALGORITHM, 2, IPFIX_CODING_UINT, 
     (char*)"reverse selectorAlgorithm", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGPACKETINTERVAL, 4, IPFIX_CODING_UINT, 
     (char*)"reverse samplingPacketInterval", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGPACKETSPACE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse samplingPacketSpace", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGTIMEINTERVAL, 8, IPFIX_CODING_NTP, 
     (char*)"reverse samplingTimeInterval", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGTIMESPACE, 8, IPFIX_CODING_NTP, 
     (char*)"reverse samplingTimeSpace", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGSIZE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse samplingSize", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGPOPULATION, 4, IPFIX_CODING_UINT, 
     (char*)"reverse samplingPopulation", (char*)"" },
   { REV_PEN, IPFIX_FT_SAMPLINGPROBABILITY, 8, IPFIX_CODING_FLOAT, 
     (char*)"reverse samplingProbability", (char*)"" },
   { REV_PEN, IPFIX_FT_DATALINKFRAMESIZE, 4, IPFIX_CODING_UINT, 
     (char*)"reverse dataLinkFrameSize", (char*)"" },
   { REV_PEN, IPFIX_FT_IPHEADERPACKETSECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse ipHeaderPacketSection", (char*)"" },
   { REV_PEN, IPFIX_FT_IPPAYLOADPACKETSECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse ipPayloadPacketSection", (char*)"" },
   { REV_PEN, IPFIX_FT_DATALINKFRAMESECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse dataLinkFrameSection", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSLABELSTACKSECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsLabelStackSection", (char*)"" },
   { REV_PEN, IPFIX_FT_MPLSPAYLOADPACKETSECTION, 65535, IPFIX_CODING_BYTES, 
     (char*)"reverse mplsPayloadPacketSection", (char*)"" },
   { REV_PEN, IPFIX_FT_PACKETSOBSERVED, 8, IPFIX_CODING_UINT, 
     (char*)"reverse packetsObserved", (char*)"" },
   { REV_PEN, IPFIX_FT_PACKETSSELECTED, 8, IPFIX_CODING_UINT, 
     (char*)"reverse packetsSelected", (char*)"" },
   { REV_PEN, IPFIX_FT_FIXEDERROR, 8, IPFIX_CODING_FLOAT, 
     (char*)"reverse fixedError", (char*)"" },
   { REV_PEN, IPFIX_FT_RELATIVEERROR, 8, IPFIX_CODING_FLOAT, 
     (char*)"reverse relativeError", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONTIMESECONDS, 4, IPFIX_CODING_UINT, 
     (char*)"reverse observationTimeSeconds", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONTIMEMILLISECONDS, 8, IPFIX_CODING_UINT, 
     (char*)"reverse observationTimeMilliseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONTIMEMICROSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse observationTimeMicroseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_OBSERVATIONTIMENANOSECONDS, 8, IPFIX_CODING_NTP, 
     (char*)"reverse observationTimeNanoseconds", (char*)"" },
   { REV_PEN, IPFIX_FT_DIGESTHASHVALUE, 8, IPFIX_CODING_UINT, 
     (char*)"reverse digestHashValue", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHIPPAYLOADOFFSET, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashIPPayloadOffset", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHIPPAYLOADSIZE, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashIPPayloadSize", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHOUTPUTRANGEMIN, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashOutputRangeMin", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHOUTPUTRANGEMAX, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashOutputRangeMax", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHSELECTEDRANGEMIN, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashSelectedRangeMin", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHSELECTEDRANGEMAX, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashSelectedRangeMax", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHDIGESTOUTPUT, 1, IPFIX_CODING_BYTES, 
     (char*)"reverse hashDigestOutput", (char*)"" },
   { REV_PEN, IPFIX_FT_HASHINITIALISERVALUE, 8, IPFIX_CODING_UINT, 
     (char*)"reverse hashInitialiserValue", (char*)"" },
   { REV_PEN, 0, -1, 0, NULL, NULL, }
};

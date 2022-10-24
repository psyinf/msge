* Serialization
	* add reflection like function to entities that put out named attributes?
		* entity can iterate serializable attributes (name, type, ref to mem)
		* attribute with
			* name - name of the field
			* type - typename for serialier
			* ref to mem - type safe accessor for read/write
			* const - will the data change
		* find a serializer for a specific type (SerializerRegistry)
			* custom type serializers in a factory-registry 
			* static serializer for basic and internal types 
		 * Serializer produces format specific representation 	
		 * Types most likely need some additional properties
			 * flat vs (sub)strutured
	add descriptor that tells us if we can serialize an entity based on its memory layout (e.g. byte-serialization)


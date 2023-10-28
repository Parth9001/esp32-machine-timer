from rest_framework import serializers
from timer.models import ESP

class TimerSerializer(serializers.Serializer):
    id = serializers.IntegerField(read_only = True)
    timer = serializers.IntegerField()

    def create(self, data):
        return ESP.objects.create(**data)
    
    def update(seld, instance,data):
        instance.timer = data.get('timer', instance.timer)

        instance.save()
        return instance
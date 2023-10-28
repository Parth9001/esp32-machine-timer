from django.db import models

# Create your models here.
class ESP(models.Model):
    timer = models.IntegerField()

    def __str__(self):
        return self.timer

class Timer(models.Model):
    timer_data = models.IntegerField()

    def __str__(self):
        return self.timer_data
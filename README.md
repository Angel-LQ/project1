利用词库文本，创建字典与索引。利用最小编辑距离算法得出编辑距离。 把编辑距离较小的候选词放入优先队列中，而优先队列利用编辑距离和词频进行排序。然后把队列中第一个或前几个单词作为返回结果。为了提高效率，添加一个缓存系统，它会自动保存查询结果；当有查询任务，会先自己我查询。客户端与服务器，用线程池的方式进行并发通信。